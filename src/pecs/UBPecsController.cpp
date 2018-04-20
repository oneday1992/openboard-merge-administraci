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
#include "gui/UBDownPalette.h"
#include "gui/UBDockPaletteWidget.h"
#include "UBAgenda.h"
#include "UBCommunicationLine.h"
#include "UBFoldersPecs.h"
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
    if (agenda)
        delete agenda;
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

        mControlLayout = new QVBoxLayout(mPecsWidget);

        // si no se pone un setContentsMargins aparece un margen en el panel de la pizarra y no se extiende a la pantalla completa
        mControlLayout->setContentsMargins(0, 0, 0, 0);
        mControlLayout->setSpacing(0);

        //Board superior
        mPpalView = new QGraphicsView(mPecsWidget);
        mPpalView->setObjectName("pecsCentralView");
        mPpalView->setInteractive(true);
        mPpalView->setMouseTracking(true);
        mPpalView->grabGesture(Qt::SwipeGesture);
        mPpalView->setTransformationAnchor(QGraphicsView::NoAnchor);
        mControlLayout->addWidget(mPpalView);
        //Fin de board superior

        //Creamos la escena ppal
        QGraphicsScene *mScenePpal = new QGraphicsScene(mPpalView);
        mPpalView->setScene(mScenePpal);



        //aplicamos geometria a la vista y tamaño a la escena, tiene que ser en los dos el mismo para que no pinte cosas raras
        //al alto se le resta uno menos por el redondeo que hace.
        mPpalView->setGeometry(0,69,QApplication::desktop()->screenGeometry().width()-100,QApplication::desktop()->screenGeometry().height()*0.70-69);
        mScenePpal->setSceneRect(0,69,QApplication::desktop()->screenGeometry().width()-100,QApplication::desktop()->screenGeometry().height()*0.70-70);
        mScenePpal->setBackgroundBrush(Qt::red);



        //Board de Comunicacion



        //Fin del board de Comunicacion

        //Añado el widget a mainwindows
        mPecsWidget->setObjectName("ubPecsContainer");
        mMainWindow->addPecsWidget(mPecsWidget);

        //QGraphicsRectItem *rectppal= mScenePpal->addRect(0,0,QApplication::desktop()->screenGeometry().width()-200,QApplication::desktop()->screenGeometry().height()*0.70-100);
        //rectppal->setBrush(Qt::green);
        //rectppal->setPos(0,0);

        QGraphicsView *mCommunicationView = new QGraphicsView(mPecsWidget);
        mCommunicationView->setObjectName("pecsCentralView");
        mCommunicationView->setInteractive(true);
        mCommunicationView->setMouseTracking(true);
        mCommunicationView->grabGesture(Qt::SwipeGesture);
        mCommunicationView->setTransformationAnchor(QGraphicsView::NoAnchor);
        mControlLayout->addWidget(mCommunicationView);


        QGraphicsScene *mSceneCommunication = new QGraphicsScene(mCommunicationView);
        mCommunicationView->setScene(mSceneCommunication);

        mCommunicationView->setGeometry(0,QApplication::desktop()->screenGeometry().height()*0.70+1,QApplication::desktop()->screenGeometry().width()-100,QApplication::desktop()->screenGeometry().height()*0.30-2);
        mSceneCommunication->setSceneRect(0,0,QApplication::desktop()->screenGeometry().width()-100,QApplication::desktop()->screenGeometry().height()*0.30-2);
        mSceneCommunication->setBackgroundBrush(Qt::gray);

        UBCommunicationLine *lineaComunicacion = new UBCommunicationLine(mPecsWidget,mSceneCommunication);
        lineaComunicacion->setGeometry(0,lineaComunicacion->screenHeight()*0.60,lineaComunicacion->screenWidth()-40,lineaComunicacion->screenHeight()*0.30);

        mSceneCommunication->addWidget(lineaComunicacion);


        QPainterPath rectppal;
        rectppal.addRoundedRect(0+border(),0,QApplication::desktop()->screenGeometry().width()-100-border(),QApplication::desktop()->screenGeometry().height()*0.30-border(),10,10);
        mSceneCommunication->addPath(rectppal);


        mPecsWidget->setLayout(mControlLayout);
        qDebug()<<mSceneCommunication->sceneRect();



        // Fin Escena

        UBFoldersPecs *carpetasPecs = new UBFoldersPecs(); //Reimplementacion de UBFeaturesWidget en UBFoldersPecs

        //Paleta de agenda de la derecha
        agenda = new UBAgenda();

        UBLeftPalette *paletaCarpetaPecs =new UBLeftPalette(mPecsWidget);
        paletaCarpetaPecs->addTab(carpetasPecs);

        UBRightPalette *paletaAgenda = new UBRightPalette(mPecsWidget);
        paletaAgenda->registerWidget(agenda);
        paletaAgenda->addTab(agenda);

       //Fin de Paletas
    }

}

int UBPecsController::border()
{
     return 20;
}
