#include <QPoint>
#include <QPointF>
#include <QPainterPath>
#include <QPainter>
#include "UBCommunicationLine.h"
#include "core/UBApplication.h"
#include "gui/UBFeaturesWidget.h"




UBCommunicationLine::UBCommunicationLine(QWidget *parent) : QWidget(parent)
{

 //   painter.setRenderHint(QPainter::Antialiasing);
   // painter.setPen(Qt::NoPen);
//    QPainterPath path;
  //  painter.setBackground(Qt::black);
 //   path.addRect(20.0, 30.0, 300, 300);
  //  painter.drawPath(path);

}

void UBCommunicationLine::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    mBackgroundBrush = QBrush(UBSettings::paletteColor);
    painter.setBrush(mBackgroundBrush);

    painter.drawRect(40, 10,this->width()-80,this->height()-100 );
    //path.addRect(40, 10,this->width()-80,this->height()-100 );
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(0, 0, width() / 2, 100);
    path.addRoundedRect(20, 30, width(),100,10,10);
    painter.drawPath(path);

}

int UBCommunicationLine::screenheight()
{
    return QApplication::desktop()->screenGeometry().height();
}

int UBCommunicationLine::screenwidth()
{
    return QApplication::desktop()->screenGeometry().width();
}
