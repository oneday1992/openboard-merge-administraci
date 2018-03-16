#include <QPoint>
#include <QPointF>
#include <QPainterPath>
#include <QPainter>
#include "PintaLineaComunicacion.h"


PintaLineaComunicacion::PintaLineaComunicacion(QWidget *parent) : QWidget(parent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    QPainterPath path;
    painter.setBackground(Qt::black);
    path.addRect(20.0, 30.0, 300, 300);
    painter.drawPath(path);

}
