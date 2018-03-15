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

UBAgendaNavigator::UBAgendaNavigator(QWidget *parent, const char *name):QGraphicsView(parent)
  , mScene(NULL)
  , mNbColumns(1)
  , mThumbnailWidth(0)
  , mThumbnailMinWidth(100)
  , mSelectedThumbnail(NULL)
{
    setObjectName(name);
    mScene = new QGraphicsScene(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(mScene);
    mThumbnailWidth = width() - 2*border();

    setFrameShadow(QFrame::Plain);


}

UBAgendaNavigator::~UBAgendaNavigator()
{

}

void UBAgendaNavigator::mouseDoubleClickEvent(QMouseEvent *event)
{
 generateThumbnails();
}

int UBAgendaNavigator::border()
{
    return 20;
}


void UBAgendaNavigator::generateThumbnails()
{
        const QPixmap *pix = new QPixmap(":pecs/10236.png");
        QGraphicsPixmapItem *picto = new QGraphicsPixmapItem(*pix);

        mScene->addItem(picto);


    // Draw the items
    //refreshScene();
        show();
}
