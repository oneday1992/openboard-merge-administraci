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


#include "UBPecsController.h"
#include "core/UBApplication.h"
#include "gui/UBMainWindow.h"
#include "gui/UBFeaturesWidget.h"
#include "gui/UBRightPalette.h"
#include "gui/UBLeftPalette.h"
#include "gui/UBDockPaletteWidget.h"
#include "UBAgenda.h"
#include <QLayout>

#include "board/UBBoardView.h"

//#include "ui_pecswindow.h"
#include "ui_mainWindow.h"

UBPecsController::UBPecsController(UBMainWindow* mainWindow)
    : QObject(mainWindow->centralWidget())
    , mMainWindow(mainWindow)
    //, mPecsUI(0)
    , mPecsWidget(0)
{
    qDebug() << "Construtor de PECS";
    //Contenido de constructor
    setupViews();


}

UBPecsController::~UBPecsController()
{
    // Destructor
    qDebug() << "Destructor PECS";
    /*if (mPecsUI)
        delete mPecsUI;
     */
}


void UBPecsController::closing()
{
    //NOOP
    qDebug() << "PECS Closing";
}


void UBPecsController::show()
{
    qDebug() << "PECS show";
}

void UBPecsController::setupViews()
{

    if (!mPecsWidget)
    {
        mPecsWidget = new QWidget(mMainWindow->centralWidget());


        mControlLayout = new QHBoxLayout(mPecsWidget);
        mControlLayout->setContentsMargins(0, 0, 0, 0);

        //Board del medio
        mCentralView = new QGraphicsView(mPecsWidget);
        mCentralView->setObjectName("pecsCentralView");
        mCentralView->setInteractive(true);
        mCentralView->setMouseTracking(true);
        mCentralView->grabGesture(Qt::SwipeGesture);
        mCentralView->setTransformationAnchor(QGraphicsView::NoAnchor);
        mControlLayout->addWidget(mCentralView);

        //Escena
        QGraphicsScene *mScene = new QGraphicsScene(mCentralView);
        mCentralView->setScene(mScene);
        QPixmap pix = QPixmap(":pecs/10236.png");
        UBPecs *picto = new UBPecs(pix,0,Qt::blue, mScene);
        mScene->addItem(picto);
        // Fin Escena
        //Fin de board del medio

        //Añado el widget a mainwindows
        mPecsWidget->setObjectName("ubPecsContainer");
        mMainWindow->addPecsWidget(mPecsWidget);

       //Paleta selección de Pecs de la izquierda
       //Paleta de agenda de la derecha
        UBFeaturesWidget *carpetasPecs = new UBFeaturesWidget();
        UBAgenda *agenda = new UBAgenda();

        UBLeftPalette *paletaCarpetaPecs =new UBLeftPalette(mPecsWidget);
        paletaCarpetaPecs->registerWidget(carpetasPecs);
        paletaCarpetaPecs->addTab(carpetasPecs);

        UBRightPalette *paletaAgenda = new UBRightPalette(mPecsWidget);
        paletaAgenda->registerWidget(agenda);
        paletaAgenda->addTab(agenda);  
       //Fin de Paletas
    }

}
