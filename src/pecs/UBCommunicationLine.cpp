#include <QPoint>
#include <QPointF>
#include <QPainterPath>
#include <QPainter>
#include "UBCommunicationLine.h"
#include "core/UBApplication.h"
#include "gui/UBFeaturesWidget.h"




UBCommunicationLine::UBCommunicationLine(QWidget *parent) : QWidget(parent)
{

}

void UBCommunicationLine::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    mBackgroundBrush = QBrush(UBSettings::paletteColor);
    painter.setBrush(mBackgroundBrush);
   // painter.drawRect(100,100,300,300 );
    painter.drawRect(40, this->height()*0.60,this->width()-80,this->height()*0.30 );
    //QPainterPath path;
    //path.setFillRule(Qt::WindingFill);
    //path.addRoundedRect(50,50,this->width() ,200,10,10);
    //painter.drawPath(path);

}

int UBCommunicationLine::screenheight()
{
    return QApplication::desktop()->screenGeometry().height();
}

int UBCommunicationLine::screenwidth()
{
    return QApplication::desktop()->screenGeometry().width();
}
