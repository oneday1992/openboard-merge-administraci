#include <QPoint>
#include <QPointF>
#include <QList>
#include <QPainterPath>
#include <QPainter>
#include "UBCommunicationLine.h"
#include "core/UBApplication.h"
#include "gui/UBFeaturesWidget.h"
#include <QLabel>
#include <QFrame>
#include "gui/UBCreateLinkPalette.h"
#include <QHBoxLayout>
#include <QWidget>
#include "UBPecs.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>


UBCommunicationLine::UBCommunicationLine(QWidget *parent, QGraphicsScene *scene) : QWidget(parent)
    ,mScene(scene)
{
    int ancho=calculateWidth(1,-100);
    int pos=posInit(ancho) + 850;

    //Añadida anterior lista como miembro de la clase. Atributo Privado
    if (listPath.count()==0){ //Si no hay elementos los añado
      for (int i=0; i<8; i++)
      {
        pictoCommunicationLine *picto =new pictoCommunicationLine();
        qreal x = calculateX(1,20)+border()+border()+pos;
        //qreal y = calculateY(30,20)+border()+border();
        qreal y = 100;

        picto->setPos(x,y);
        pos=pos+pictoWidth()+separatorPicto();
        listPath.append(picto);
        mScene->addItem(picto);
      }
    }
}

/*
void UBCommunicationLine::paintEvent(QPaintEvent *e)
{
   qWarning()<<"Entrando en método paintEvent";

    //pintamos el cuadro de drag and drop
    //painter.setPen(Qt::DotLine);
    int ancho=calculateWidth(1,-100);
    int pos=posInit(ancho);

    //Añadida anterior lista como miembro de la clase. Atributo Privado
    if (listPath.count()==0){ //Si no hay elementos los añado
      for (int i=0; i<8; i++)
      {
        pictoCommunicationLine *path2 =new pictoCommunicationLine(0,i,mScene);
        qreal x = calculateX(1,20)+border()+border()+pos;
        qreal y = calculateY(1,20)+border()+border();
        //qreal y = 200;

        path2->setPos(x,y);
        pos=pos+pictoWidth()+separatorPicto();
        listPath.append(path2);
        mScene->addItem(path2);
      }
    }else{
        //Recorro la lista de QPainterPath
        for(int i = 0; i < listPath.count(); i++)
        {
            //Hay que pasarle un qPainterPath, no se puede pasar un QWidget
          //mScene->addItem(listPath[i]);
        }
    }
    e->accept();

}
*/
int UBCommunicationLine::border()
{
    return 20;
}

int UBCommunicationLine::calculateX(double percent, int displaced)
{
    return this->width()*(percent/100)+displaced;
}

int UBCommunicationLine::calculateY(double percent,int displaced)
{
    return QApplication::desktop()->height()*(percent/100)+displaced;
}

int UBCommunicationLine::calculateWidth(double percent,int displaced)
{
    if (percent==1)
    {
        return this->width()+displaced;
    }
    else
    {
        return this->width()*(percent/100)+displaced;
    }

}

int UBCommunicationLine::calculateHeight(double percent,int displaced)
{
    if (percent==1)
    {
        return this->height()+displaced;
    }
    else
    {
        return this->height()*(percent/100)+displaced;
    }
}

int UBCommunicationLine::pictoWidth()
{
    return 180;
}

int UBCommunicationLine::pictoHeight()
{
    return 180;
}

int UBCommunicationLine::separatorPicto()
{
    return 20;
}

int UBCommunicationLine::posInit(int ancho)
{
    int size = pictoWidth() * 8 + separatorPicto() * 8;
    int resto = ancho - size;
    return resto/2;
}

int UBCommunicationLine::screenHeight()
{
    return QApplication::desktop()->screenGeometry().height();
}

int UBCommunicationLine::screenWidth()
{
    return QApplication::desktop()->screenGeometry().width();
}


/*
 *
 *
 *
 * Implementación de la clase pictoCommunicationLine
 *
 *
 *
 */


pictoCommunicationLine::pictoCommunicationLine(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(parent)
    ,width(180)
    ,height(180)
{
    setAcceptDrops(true);

    QPixmap pixmap = QPixmap(":pecs/pictoBlanco.png");
    setPixmap(pixmap.scaled(width,height,Qt::KeepAspectRatio));
    setFlag(QGraphicsItem::ItemIsMovable,false);
}

pictoCommunicationLine::~pictoCommunicationLine()
{
    qWarning() << "Destructor de pictoCommunicationLine";
}




void pictoCommunicationLine::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();

}

void pictoCommunicationLine::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

        QPixmap pixmap = this->pixmap();
        QPainter painter;
        painter.begin(&pixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 90));
        painter.setPen(QPen(Qt::white,8,Qt::SolidLine));
        painter.drawRoundRect(pixmap.rect());
        painter.end();
        this->setPixmap(pixmap);

        event->setDropAction(Qt::MoveAction);
        event->accept();

}

void pictoCommunicationLine::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    QPixmap pixmap = QPixmap(":pecs/pictoBlanco.png");
    setPixmap(pixmap.scaled(width,height,Qt::KeepAspectRatio));
    event->accept();
}

void pictoCommunicationLine::dropEvent(QGraphicsSceneDragDropEvent *event)
{

    if (event->mimeData()->hasFormat("PictoPecs")) {
        QByteArray itemData = event->mimeData()->data("PictoPecs");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;


        setPixmap(pixmap);
        setAcceptDrops(false);
        setFlag(QGraphicsItem::ItemIsMovable);
        setCursor(Qt::OpenHandCursor);
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
            setPixmap(pixmap.scaled(width,height,Qt::KeepAspectRatio));

            pixmap=this->pixmap();
            QPainter painter;
            painter.begin(&pixmap);
            painter.setPen(QPen(Qt::red,8,Qt::SolidLine));
            painter.drawRect(QRect(pixmap.rect().x()+4,pixmap.rect().y()+4,pixmap.rect().width()-8,pixmap.rect().height()-8));
            painter.end();
            setPixmap(pixmap);

            setAcceptDrops(false);
            setFlag(QGraphicsItem::ItemIsMovable);
            setCursor(Qt::OpenHandCursor);
            event->accept();
        }
    }


}

void pictoCommunicationLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //setCursor(Qt::ClosedHandCursor);

    if (flags() & QGraphicsItem::ItemIsMovable){
        QPixmap pixmap = this->pixmap();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << QPointF(event->pos() - this->pos());
        QMimeData *mimeData = new QMimeData;

        mimeData->setData("PictoPecs", itemData);

        QDrag *drag = new QDrag(event->widget());
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);

        QCursor cursor(Qt::WaitCursor);
        drag->setDragCursor(cursor.pixmap(), Qt::MoveAction);

        QPointF aux = event->pos();

        drag->setHotSpot(aux.toPoint());
        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 90));
        painter.end();
        this->setPixmap(tempPixmap);

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
            QPixmap original = QPixmap(":pecs/pictoBlanco.png");
            this->setPixmap(original.scaled(width,height,Qt::KeepAspectRatio));
            //Colocamos propiedades iniciales
            setAcceptDrops(true);
            setFlag(QGraphicsItem::ItemIsMovable,false);
            setCursor(Qt::ArrowCursor);

        } else {
            this->setPixmap(pixmap);
        }

    }
        QGraphicsPixmapItem::mousePressEvent(event);
        event->accept();

}



