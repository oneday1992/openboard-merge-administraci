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
#include "UBAgenda.h"
#include <QGraphicsView>
#include "globals/UBGlobals.h"


UBAgenda::UBAgenda(QWidget *parent, const char *name) : UBDockPaletteWidget(parent)
  , mLayout(NULL)
  , mNavigator(NULL)
{

    setObjectName(name);
    mName = "Agenda";
    mVisibleState = true;

    SET_STYLE_SHEET();

    mIconToRight = QPixmap(":images/pages_open.png");
    mIconToLeft = QPixmap(":images/pages_close.png");

    mNavigator = new UBAgendaNavigator(this);

//Main layout including all the widgets in palette
    mLayout = new QVBoxLayout(this);
    setLayout(mLayout);
    mLayout->addWidget(mNavigator);

}

UBAgenda::~UBAgenda()
{
    qWarning()<<"Destructor de UBAgenda";
    //Destructor
    if(NULL != mNavigator)
    {
        delete mNavigator;
        mNavigator = NULL;
    }
    if(NULL != mLayout)
    {
        delete mLayout;
        mLayout = NULL;
    }

}



