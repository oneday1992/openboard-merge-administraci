#include <QPoint>
#include <QPointF>
#include <QPainterPath>
#include <QPainter>
#include "UBCommunicationLine.h"
#include "core/UBApplication.h"
#include "gui/UBFeaturesWidget.h"
#include <QLabel>
#include <QFrame>
#include "gui/UBCreateLinkPalette.h"




UBCommunicationLine::UBCommunicationLine(QWidget *parent) : QWidget(parent)
{

}

void UBCommunicationLine::paintEvent(QPaintEvent *e)
{
    /**
    // Usamos esta parte del codigo para hacer pruebas.

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    mBackgroundBrush = QBrush(UBSettings::paletteColor);
    painter.setPen(Qt::NoPen);

    // painter.setBrush(mBackgroundBrush);
    painter.setBrush(mBackgroundBrush);

    QPainterPath borderPath;
    borderPath.setFillRule(Qt::WindingFill);


    borderPath.addRoundedRect(0, 0, width(), height(), 15,15);
    borderPath.addRoundedRect(border(), border(), width() - 2 * border(), height() - 2 * border(), 15,15);
    painter.drawPath(borderPath);
    painter.setBrush(QBrush(QColor(170, 170 ,170)));
    painter.drawRoundedRect(border(), border(), width() - 2 * border(), height() - 2 * border(), 15,15);
    */


     //codigo
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
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

    //pintamos el cuadro de drag and drop
    painter.setPen(Qt::DotLine);
    int ancho=calculateWidth(1,-160);
    int pos=posInit(ancho);
    for (int i=0; i<8; i++)
    {
        QPainterPath path;
        path.addRoundedRect(calculateX(1,20)+border()+border()+pos,calculateY(63)+border()+border(),pictoWidth(),pictoHeight(),10,10);
        painter.drawPath(path);
        pos=pos+pictoWidth()+separatorPicto();

    }
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

void UBCommunicationLine::dragMoveEvent(QDragMoveEvent *event)
{
    QWidget::dragMoveEvent(event);
    event->acceptProposedAction();
}
