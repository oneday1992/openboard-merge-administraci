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
//setAcceptDrops(true);
    //Tenemos que crear un layout horizontal donde añadir cada widget donde se va a alojar cada picto.
    layout = new QHBoxLayout(this);
}

void UBCommunicationLine::paintEvent(QPaintEvent *e)
{
   qWarning()<<"Entrando en método paintEvent";

    //codigo
 //   QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing,true);
//    mBackgroundBrush = QBrush(UBSettings::paletteColor);
  //  painter.setPen(Qt::NoPen);
    //painter.setBrush(mBackgroundBrush);

    //pintamos el recuadro grande
//    pictoCommunicationLine *painter =new pictoCommunicationLine(0,i,mScene);
 // mScene->addRect(100,100,20,20,Qt::NoPen,UBSettings::paletteColor);
   // mScene->addRect(calculateX(1,20)+border(),calculateY()+border(),calculateWidth(1,-90),calculateHeight(1,-60),Qt::NoPen,UBSettings::paletteColor);
  //  QRectF *item = new QRectF;
  //  mScene->addRect(100,100,200,200);

   // QGraphicsRectItem
/*    painter.drawRoundedRect(calculateX(1,20), calculateY(),calculateWidth(1,-50),calculateHeight(1,-20),10,10);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

*/
    //pintamos el recuadro de relleno
    //path.addRoundedRect(calculateX(1,20)+border(),calculateY()+border(),calculateWidth(1,-90),calculateHeight(1,-60),10,10);
   // painter.drawPath(path);

  //  mScene->setSceneRect(calculateX(1,20)+border(),calculateY()+border(),calculateWidth(1,-90),calculateHeight(1,-60));
  //  qWarning()<< calculateX(1,20)+border() << calculateY()+border() << calculateWidth(1,-90) << calculateHeight(1,-60);
  //  qWarning()<< "Datos de Scene: " << mScene->sceneRect();

    //pintamos el cuadro de drag and drop
    //painter.setPen(Qt::DotLine);
//    int ancho=calculateWidth(1,-100);
  //  int pos=posInit(ancho);
    //Añadida anterior lista como miembro de la clase. Atributo Privado
//    if (listPath.count()==0){ //Si no hay elementos los añado
  //    for (int i=0; i<8; i++)
    //  {
      //  pictoCommunicationLine *path2 =new pictoCommunicationLine(0,i,mScene);
        //qreal x = calculateX(1,20)+border()+border()+pos;
//        qreal y = calculateY(30,20)+border()+border();
  //      path2->setPos(x,y);
    //    pos=pos+pictoWidth()+separatorPicto();
      //  listPath.append(path2);
//        mScene->addItem(path2);
  //    }
//    }else{
        //Recorro la lista de QPainterPath
  //      for(int i = 0; i < listPath.count(); i++)
    //    {
            //Hay que pasarle un qPainterPath, no se puede pasar un QWidget
      //    mScene->addItem(listPath[i]);
//        }
//    }
  //  e->accept();
}

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
void UBCommunicationLine::dragMoveEvent(QDragMoveEvent *event)
{
    QWidget::dragMoveEvent(event);
    event->acceptProposedAction();
}

void UBCommunicationLine::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}
*/
pictoCommunicationLine::pictoCommunicationLine(QGraphicsPixmapItem *parent, int i, QGraphicsScene *scene) : QGraphicsPixmapItem(parent)
    ,numero(i)
    ,mScene(scene)
    ,width(180)
    ,height(180)
{
    setAcceptDrops(true);

    setCursor(Qt::OpenHandCursor);
    //setAcceptedMouseButtons(Qt::LeftButton);

    QPixmap pixmap = QPixmap(":pecs/pictoBlanco.png");
    setPixmap(pixmap.scaled(width,height,Qt::KeepAspectRatio));
    qWarning()<<"Constructor de pictoCommnication: "<<numero;

}




void pictoCommunicationLine::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();

}

void pictoCommunicationLine::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

        event->setDropAction(Qt::MoveAction);
        event->accept();


    qWarning()<<"Picto en casilla: " << numero;
 //   event->accept();

}

void pictoCommunicationLine::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

    event->accept();
}

void pictoCommunicationLine::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QList<QUrl> urls;
    urls = event->mimeData()->urls();
    qWarning()<<urls;
    QList<QUrl>::iterator i;
    for (i=urls.begin();i!=urls.end();i++){
        QPixmap pix = QPixmap(i->path());
        //UBPecs *picto = new UBPecs(pix,0,Qt::red,mScene);
        setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
        //Añado
        //picto->setPos(mQPainterPath->currentPosition());

        //qWarning()<< picto->pos().x() << picto->pos().y() << picto->sceneBoundingRect() << picto->boundingRect();
        //mScene->addItem(picto);
     setAcceptDrops(false);
     setFlag(QGraphicsItem::ItemIsSelectable);
     setFlag(QGraphicsItem::ItemIsMovable);
     //setFlag(QGraphicsItem::ItemSendsGeometryChanges);


     /*setFlag(QGraphicsItem::ItemIsMovable);
     setFlag(QGraphicsItem::ItemClipsToShape,true);
     setFlag(QGraphicsItem::ItemClipsChildrenToShape);
*/


    }

    event->accept();
}

void pictoCommunicationLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);

    QPixmap pixmap = this->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPointF(event->pos() - this->pos());
    QMimeData *mimeData = new QMimeData;

    mimeData->setData("application/x-dnditemdata", itemData);
//! [2]

//! [3]
    QDrag *drag = new QDrag(event->widget());
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    //QPointF aux =event->pos() - this->pos();
    QPointF aux = event->pos();

    drag->setHotSpot(aux.toPoint());
//! [3]
    QPixmap tempPixmap = QPixmap(":pecs/pictoBlanco.png");
    setPixmap(tempPixmap.scaled(width,height,Qt::KeepAspectRatio));
    //QPixmap tempPixmap = pixmap;
    //QPainter painter;
    //painter.begin(&tempPixmap);
    //painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    //painter.end();
    this->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        //child->close();
    } else {
        //child->show();
        //child->setPixmap(pixmap);
    }
    QGraphicsPixmapItem::mousePressEvent(event);
    event->accept();
}


void pictoCommunicationLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qWarning()<<"Suelto tecla de picto: " << numero;
    setCursor(Qt::OpenHandCursor);
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    event->accept();
}

