/*
 * OpenBoard
 * Authors: Elisa Aparicio Pérez (isabel.aparicio@juntaex.es)
 *          Ismael Campos Suárez (ismael.campos@juntaex.es)
 *          Rafael Jesús García Perdigón (rafael.garciap@juntaex.es)
 *          Álvaro Rubio Largo (alvaro.rubio@juntaex.es)
 *
 * Creation Date : 27/02/2018
 * Copyright (C) 2018 Junta de Extremadura.
 *
 * This file is part of OpenBoard.
 *
 * OpenBoard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * OpenBoard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenBoard. If not, see <http://www.gnu.org/licenses/>.
 */

#include "UBPecs.h"
#include <QGraphicsItem>
#include <QPainter>
#include "core/UBApplication.h"
#include "board/UBBoardController.h"
#include "domain/UBGraphicsScene.h"


UBPecs::UBPecs(const QPixmap &pixmap, QGraphicsItem *parent, Qt::GlobalColor color, QGraphicsScene *scene) : QGraphicsPixmapItem(pixmap,parent)
  , width(180)
  , height(180)
  , mColor(color)
  , noPen(false)
{
   mScene = scene;
   setPixmap(pixmap.scaled(width,height,Qt::KeepAspectRatio));
   setFlag(QGraphicsItem::ItemIsMovable);

}

UBPecs::~UBPecs()
{
   qWarning()<<"Destructor Picto";
}

//Pinto el borde del picto con el color elegido
void UBPecs::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setRenderHint(QPainter::Antialiasing,true);
    //painter->setRenderHint(QPainter::SmoothPixmapTransform,true);
    if(noPen==true)
        painter->setPen(Qt::NoPen);
    else
        painter->setPen(QPen(mColor,8,Qt::SolidLine));

    QGraphicsPixmapItem::paint(painter,option,widget);
    painter->drawRect(this->pixmap().rect());
}


void UBPecs::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    noPen=true;
    QGraphicsPixmapItem::mousePressEvent(event);
    mScene->update();
}

void UBPecs::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    noPen=false;
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    // force refresh, QT is a bit lazy and take a lot of time (nb item ^2 ?) to trigger repaint
    mScene->update();
}

