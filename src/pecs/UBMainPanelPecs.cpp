#include "UBMainPanelPecs.h"
#include <qevent.h>
#include <QDebug>
#include "UBCommunicationLine.h"
#include <QMimeData>
#include <QGraphicsScene>


UBMainPanelPecs::UBMainPanelPecs(QWidget *parent, QGraphicsScene *scene) : QWidget(parent)
    ,mScene(scene)
{
    setAcceptDrops(true);
}

void UBMainPanelPecs::dragEnterEvent(QDragEnterEvent *event)
{
    qWarning() << "Entrando en panel principal de Pecs para drops";
    event->accept();
}

void UBMainPanelPecs::dropEvent(QDropEvent *event)
{

    if (event->mimeData()->hasFormat("PictoPecs")) {
        QByteArray itemData = event->mimeData()->data("PictoPecs");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        pictoCommunicationLine *picto =new pictoCommunicationLine();

        picto->setPixmap(pixmap);
        picto->setAcceptDrops(false);
        picto->setFlag(QGraphicsItem::ItemIsMovable);
        picto->setCursor(Qt::OpenHandCursor);
        //picto->setPos(event->pos().x(),event->pos().y());
        mScene->addItem(picto);

        event->setDropAction(Qt::MoveAction);
        event->accept();
        //event->acceptProposedAction();
    }
    else{
        QList<QUrl> urls;
        urls = event->mimeData()->urls();
        qWarning()<<urls;
        QList<QUrl>::iterator i;
        for (i=urls.begin();i!=urls.end();i++){
            QPixmap pixmap = QPixmap(i->path());
            pictoCommunicationLine *picto =new pictoCommunicationLine();
            picto->setPixmap(pixmap.scaled(180,180,Qt::KeepAspectRatio));

            pixmap=picto->pixmap();
            QPainter painter;
            painter.begin(&pixmap);
            painter.setPen(QPen(Qt::red,8,Qt::SolidLine));
            painter.drawRect(QRect(pixmap.rect().x()+4,pixmap.rect().y()+4,pixmap.rect().width()-8,pixmap.rect().height()-8));
            painter.end();
            picto->setPixmap(pixmap);
            picto->setAcceptDrops(false);
            picto->setFlag(QGraphicsItem::ItemIsMovable);
            picto->setCursor(Qt::OpenHandCursor);
            picto->setPos(event->pos().x(),event->pos().y());
            mScene->addItem(picto);
            event->accept();
        }
    }

}


