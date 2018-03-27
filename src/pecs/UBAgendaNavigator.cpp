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
#include "domain/UBGraphicsWidgetItem.h"
#include "gui/UBThumbnailWidget.h"
#include <QWebView>
#include <QList>
#include <QUrl>

UBAgendaNavigator::UBAgendaNavigator(QWidget *parent, const char *name):QGraphicsView(parent)
  , mScene(NULL)

{
    setObjectName(name);
    mScene = new QGraphicsScene(this);

    setScene(mScene);


}

UBAgendaNavigator::~UBAgendaNavigator()
{
   qWarning()<<"Destructor UBAgendaNavigator";
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

void UBAgendaNavigator::dropEvent(QDropEvent *event)
{


     QList<QUrl> urls;
     urls = event->mimeData()->urls();
     qWarning()<<urls;
     QList<QUrl>::iterator i;
     for (i=urls.begin();i!=urls.end();i++){
         QPixmap pix = QPixmap(i->path());
         UBPecs *picto = new UBPecs(pix,0,Qt::red,mScene);
         //Añado a la lista de Items
           mPecs.append(picto);
     }
     // Draw the items
     refreshScene();

    //prevent features in UBFeaturesWidget deletion from the model when event is processing inside
    //Qt base classes
    if (event->dropAction() == Qt::MoveAction) {
        event->setDropAction(Qt::CopyAction);
    }
}

void UBAgendaNavigator::dragMoveEvent(QDragMoveEvent *event)
{
    QGraphicsView::dragMoveEvent(event);
    event->acceptProposedAction();
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
        UBPecs *picto = new UBPecs(pix,0,Qt::red,mScene);

        //Añado a la lista de Items
          mPecs.append(picto);

        // Draw the items
        refreshScene();

}
