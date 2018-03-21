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
    painter.setPen(Qt::NoPen);
    painter.setBrush(mBackgroundBrush);
    //pintamos el recuadro grande
    painter.drawRoundedRect(calculateX(1,20), calculateY(60),calculateWidth(1,-80),calculateHeight(30),10,10 );
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    //pintamos el recuadro de relleno
    path.addRoundedRect(calculateX(1,20)+border(),calculateY(60)+border(),calculateWidth(1,-120),calculateHeight(30,-40),10,10);
    painter.drawPath(path);

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
    return this->height()*(percent/100)+displaced;
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

int UBCommunicationLine::screenHeight()
{
    return QApplication::desktop()->screenGeometry().height();
}

int UBCommunicationLine::screenWidth()
{
    return QApplication::desktop()->screenGeometry().width();
}
