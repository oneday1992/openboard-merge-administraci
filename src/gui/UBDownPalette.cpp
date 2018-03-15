/*
 * Copyright (C) 2015-2016 Département de l'Instruction Publique (DIP-SEM)
 *
 * Copyright (C) 2013 Open Education Foundation
 *
 * Copyright (C) 2010-2013 Groupement d'Intérêt Public pour
 * l'Education Numérique en Afrique (GIP ENA)
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




//Clase creada para customizar la linea de comunicaciones de PECS.
// Class created to customize the communications line of PECS.


#include "UBDownPalette.h"
#include "core/UBApplication.h"
#include "board/UBBoardController.h"
#include "core/memcheck.h"



//The constructor
//El constructor

UBDownPalette::UBDownPalette(QWidget *parent, const char *name) :
    UBDockPalette(eUBDockPaletteType_DOWN, parent)
{
    setObjectName(name);
    setOrientation(eUBDockOrientation_Bottom);
    mCollapseWidth = 150;
    bool isCollapsed = false;
    if(mCurrentMode == eUBDockPaletteWidget_BOARD){
        mLastWidth = UBSettings::settings()->downLibPaletteBoardModeWidth->get().toInt();
        isCollapsed = UBSettings::settings()->downLibPaletteBoardModeIsCollapsed->get().toBool();
    }
    else{
        mLastWidth = UBSettings::settings()->downLibPaletteDesktopModeWidth->get().toInt();
        isCollapsed = UBSettings::settings()->downLibPaletteDesktopModeIsCollapsed->get().toBool();

    }
    if(isCollapsed)
        //resize(0,parentWidget()->height());
        resize(parentWidget()->width(),0);
    else
        //resize(mLastWidth, parentWidget()->height());
        resize(parentWidget()->width(),mLastWidth);
}

/**
 * The destructor
 * El destructor
 */
UBDownPalette::~UBDownPalette()
{
}

/**
 * \brief Handle the mouse move event
 * @event as the mouse move event
 * Manejar el evento de mover el mouse
 * @event como el evento de movimiento del mouse
 */
void UBDownPalette::mouseMoveEvent(QMouseEvent *event)
{
/*    if(mCanResize)
    {
        UBDockPalette::mouseMoveEvent(event);
    }*/
}

/**
 * \brief Handle the resize event
 * @param event as the resize event
 * Manejar el evento de cambio de tamaño
 * @ evento param como el evento de cambio de tamaño
 */
void UBDownPalette::resizeEvent(QResizeEvent *event)
{
    int newWidth = width();
    if(mCurrentMode == eUBDockPaletteWidget_BOARD){
        if(newWidth > mCollapseWidth)
            UBSettings::settings()->downLibPaletteBoardModeWidth->set(newWidth);
        UBSettings::settings()->downLibPaletteBoardModeIsCollapsed->set(newWidth == 0);
    }
    else{
        if(newWidth > mCollapseWidth)
            UBSettings::settings()->downLibPaletteDesktopModeWidth->set(newWidth);
        UBSettings::settings()->downLibPaletteDesktopModeIsCollapsed->set(newWidth == 0);
    }
    UBDockPalette::resizeEvent(event);
    emit resized();
}

/**
 * \brief Update the maximum width
 * Actualiza en ancho maximo
 *
 */
void UBDownPalette::updateMaxWidth()
{
    setMaximumWidth((int)(parentWidget()->width()));
    setMaximumHeight(parentWidget()->height()* 0.45);
    setMinimumHeight(parentWidget()->height());
}

bool UBDownPalette::switchMode(eUBDockPaletteWidgetMode mode)
{
    int newModeWidth;
    if(mode == eUBDockPaletteWidget_BOARD){
        mLastWidth = UBSettings::settings()->downLibPaletteBoardModeWidth->get().toInt();
        newModeWidth = mLastWidth;
        if(UBSettings::settings()->downLibPaletteBoardModeIsCollapsed->get().toBool())
            newModeWidth = 0;
    }
    else{
        mLastWidth = UBSettings::settings()->downLibPaletteDesktopModeWidth->get().toInt();
        newModeWidth = mLastWidth;
        if(UBSettings::settings()->downLibPaletteDesktopModeIsCollapsed->get().toBool())
            newModeWidth = 0;
    }
    resize(newModeWidth,height());
    return UBDockPalette::switchMode(mode);
}


//} //fin de la clase


