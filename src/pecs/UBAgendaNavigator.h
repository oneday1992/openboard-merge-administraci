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

#ifndef UBAGENDANAVIGATOR_H
#define UBAGENDANAVIGATOR_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "gui/UBThumbnailWidget.h"
#include "document/UBDocumentContainer.h"
#include <QBoxLayout>


class UBAgendaNavigator : public QGraphicsView
{
    Q_OBJECT
public:
    UBAgendaNavigator(QWidget* parent=0, const char* name="agendaNavigator");
    ~UBAgendaNavigator();

    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    int border();
    void refreshScene();

    /** The scene */
    QGraphicsScene* mScene;
   /** The list of current thumbnails with labels*/
    QList<QGraphicsItem*> mItems;
    /** The current number of columns */
    int mNbColumns;
    /** The current thumbnails width */
    int mThumbnailWidth;
    /** The current thumbnails minimum width */
    int mThumbnailMinWidth;
    /** The selected thumbnail */
    UBSceneThumbnailNavigPixmap* mSelectedThumbnail;

public slots:
     void generateThumbnails();
};

#endif // UBAGENDANAVIGATOR_H
