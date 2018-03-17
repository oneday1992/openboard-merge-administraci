#include <QPoint>
#include <QPointF>
#include <QPainterPath>
#include <QPainter>
#include "PintaLineaComunicacion.h"


PintaLineaComunicacion::PintaLineaComunicacion(QWidget *parent) : QWidget(parent)
{

 //   painter.setRenderHint(QPainter::Antialiasing);
   // painter.setPen(Qt::NoPen);
//    QPainterPath path;
  //  painter.setBackground(Qt::black);
 //   path.addRect(20.0, 30.0, 300, 300);
  //  painter.drawPath(path);

}

void PintaLineaComunicacion::paintEvent(QPaintEvent *e)
{
     QPainter painter(this);
   //  painter.drawLine(10, 10, 650, 500);
     // painter.setPen(Qt::red);
      painter.drawRect(40, 10, 300, 400);
   //   painter.setPen(QPen(Qt::green, 5));
     // painter.setBrush(Qt::blue);
   //   painter.drawEllipse(50, 150, 400, 200);
   //  QPainterPath path;
     //painter.setBackground(Qt::black);
    // path.addRect(20.0, 30.0, 300, 300);
     //painter.drawPath(path);
}
