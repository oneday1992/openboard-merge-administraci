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
#include "UBAgendaNavigator.h"
#include <QFile>
#include <QBoxLayout>

UBAgendaNavigator::UBAgendaNavigator(QWidget *parent, const char *name):QGraphicsView(parent)
  , mScene(NULL)

{
    setObjectName(name);
    mScene = new QGraphicsScene(this);

    setScene(mScene);


}

UBAgendaNavigator::~UBAgendaNavigator()
{
    if(NULL != mScene)
    {
        delete mScene;
        mScene = NULL;
    }
    mPecs.clear();
}

void UBAgendaNavigator::mouseDoubleClickEvent(QMouseEvent *event)
{
 generateListPecs();
}

void UBAgendaNavigator::refreshScene()
{

    for(int i = 0; i < mPecs.count(); i++)
    {
        // Get the item
        QGraphicsItem *item = mPecs[i];
        item->setPos(0,i*200);
        mScene->addItem(item);
    }

}


void UBAgendaNavigator::generateListPecs()
{
        QPixmap pix = QPixmap(":pecs/10236.png");
        QPixmap pixmap =pix.scaled(300, 180,Qt::KeepAspectRatio);
        pix =pix.scaled(200, 180,Qt::KeepAspectRatio);
        QGraphicsPixmapItem *picto = new QGraphicsPixmapItem(pixmap);
        QGraphicsPixmapItem *picto2 = new QGraphicsPixmapItem(pix);

        QGraphicsRectItem *item = new QGraphicsRectItem();
        // izquierda, arriba, ancho y alto
          item->setRect(0, 0, 180, 180);
          // Línea: Ancho y estilo
          item->setPen(QPen(Qt::blue,4,Qt::SolidLine));
          // Relleno: Color y estilo.
          item->setBrush(QBrush(Qt::green,Qt::SolidPattern));


        //Añado a la lista de Items
          mPecs.append(picto);
          mPecs.append(item);
          mPecs.append(picto2);

        // Draw the items
        refreshScene();

}
