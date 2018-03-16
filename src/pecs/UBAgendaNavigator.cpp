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
  , mNbColumns(1)
  , mThumbnailWidth(0)
  , mThumbnailMinWidth(100)
  , mSelectedThumbnail(NULL)
{
    setObjectName(name);
    mScene = new QGraphicsScene(this);

    setScene(mScene);
    mThumbnailWidth = width() - 2*border();

    setFrameShadow(QFrame::Plain);


}

UBAgendaNavigator::~UBAgendaNavigator()
{
    if(NULL != mScene)
    {
        delete mScene;
        mScene = NULL;
    }
    mItems.clear();
}

void UBAgendaNavigator::mouseDoubleClickEvent(QMouseEvent *event)
{
 generateThumbnails();
}

int UBAgendaNavigator::border()
{
    return 20;
}

void UBAgendaNavigator::refreshScene()
{
    qreal thumbnailHeight = mThumbnailWidth / UBSettings::minScreenRatio;

    for(int i = 0; i < mItems.count(); i++)
    {
        // Get the item
        QGraphicsItem *item = mItems[i];
        //int columnIndex = i % mNbColumns;
        //int rowIndex = i / mNbColumns;
        //item->ensureVisible(rowIndex, columnIndex, mThumbnailWidth, thumbnailHeight);
        mScene->addItem(item);
    }
    //scene()->setSceneRect(scene()->itemsBoundingRect());



        //setRenderHints( QPainter::Antialiasing );
        //show();
}


void UBAgendaNavigator::generateThumbnails()
{
        QPixmap pix = QPixmap(":pecs/10236.png");
        QPixmap pixmap =pix.scaled(200, 100);

        QGraphicsPixmapItem *picto = new QGraphicsPixmapItem(pixmap);
        QGraphicsPixmapItem *picto2 = new QGraphicsPixmapItem(pix);


        //QGraphicsPixmapItem *picto = new QGraphicsPixmapItem(pix);


        //mScene->addItem(picto);

        QGraphicsRectItem *item = new QGraphicsRectItem();
        // izquierda, arriba, ancho y alto
          item->setRect(0, 0, 200, 100);
          // Línea: Ancho y estilo
          item->setPen(QPen(Qt::blue,4,Qt::SolidLine));
          // Relleno: Color y estilo.
          item->setBrush(QBrush(Qt::green,Qt::SolidPattern));

        //mScene->addItem(item);

        //Añado a la lista de Items
          //mItems.append(picto);
          //mItems.append(item);
          //mItems.append(picto2);

          mScene->addItem(picto);



    // Draw the items
    refreshScene();

}
