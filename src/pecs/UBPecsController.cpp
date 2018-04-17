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

        //Board del medio
        mCentralView = new QGraphicsView(mPecsWidget);
        mCentralView->setObjectName("pecsCentralView");
        mCentralView->setInteractive(true);
        mCentralView->setMouseTracking(true);
        mCentralView->grabGesture(Qt::SwipeGesture);
        mCentralView->setTransformationAnchor(QGraphicsView::NoAnchor);
        mControlLayout->addWidget(mCentralView);
        //Fin de board del medio

        //Añado el widget a mainwindows
        mPecsWidget->setObjectName("ubPecsContainer");
        mMainWindow->addPecsWidget(mPecsWidget);

        // Creamos una escena diferente para añadir la linea de comunicacion y otra escena para la ventana ppal
        //Escena principal
   //     QGraphicsScene *mScenePpal = new QGraphicsScene(mCentralView);
    //    mCentralView->setScene(mScenePpal);
      //  mScenePpal->setSceneRect(0,0,QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height()*0.70);
    //    mScenePpal->addRect(10,10,100,100);
        //Escena de la linea de comunicacion
        QGraphicsScene *mSceneCentral = new QGraphicsScene(mCentralView);
        mCentralView->setScene(mSceneCentral);
        int y=QApplication::desktop()->screenGeometry().height()*0.70+1;
        int ancho=QApplication::desktop()->screenGeometry().width();
        int alto=QApplication::desktop()->screenGeometry().height()*0.30-1;
        int pantallay=QApplication::desktop()->screenGeometry().height();
     //   mSceneCommunication->setSceneRect(0,68,QApplication::desktop()->screenGeometry().width(), QApplication::desktop()->screenGeometry().height()-68);
           //mSceneCommunication->setSceneRect(0,(QApplication::desktop()->screenGeometry().height()-68)*0.70,QApplication::desktop()->screenGeometry().width(),(QApplication::desktop()->screenGeometry().height()-68)*0.30);
        //mSceneCommunication->setSceneRect(0,(QApplication::desktop()->screenGeometry().height()-70)*0.70,QApplication::desktop()->screenGeometry().width(),(QApplication::desktop()->screenGeometry().height()-70)*0.30);
        //mSceneCommunication->setSceneRect(0,538,1300,229);
        //qDebug () << mSceneCommunication-> sceneRect ();
        //UBCommunicationLine *lineaComunicacion = new UBCommunicationLine(mPecsWidget,mSceneCommunication);
     //   int x=lineaComunicacion->screenHeight()*0.60;
        //mCentralView->setScene(mSceneCommunication);

        mCentralView->setGeometry(0,0,1920-100,(1079-72)*0.7);
        mSceneCentral->setSceneRect(0,0,1920-100,(1079-72)*0.7);

        mSceneCentral->setBackgroundBrush(Qt::red);
        qWarning()<<"*********************************************  "<<(QApplication::desktop()->screenGeometry().height()-70)*0.70;
    //    lineaComunicacion->setGeometry(0,lineaComunicacion->screenHeight()*0.60,lineaComunicacion->screenWidth()-40,lineaComunicacion->screenHeight()*0.30);
        //mSceneCommunication->addRect(0,700,QApplication::desktop()->screenGeometry().width(),(QApplication::desktop()->screenGeometry().height()-68)*0.30);

        //QGraphicsRectItem *rectppal= mSceneCommunication->addRect(0,0,QApplication::desktop()->screenGeometry().width(),50);
        //QGraphicsRectItem *rectppal= mSceneCentral->addRect(0,0,QApplication::desktop()->screenGeometry().width()-20,50);
        QGraphicsRectItem *rectppal= mSceneCentral->addRect(0,0,1920-100,500);
        rectppal->setBrush(Qt::green);
        qWarning() << "Tamaño de rect principal" << rectppal->rect();
        rectppal->setPos(0,0);

        QGraphicsView *mCommunicationView = new QGraphicsView(mPecsWidget);
        QGraphicsScene *mSceneCommunication = new QGraphicsScene(mCommunicationView);
        mCommunicationView->setGeometry(0,1080*0.7,1920-100,(1079-69)*0.3);
        mSceneCommunication->setSceneRect(0,0,1920-100,(1079-69)*0.3);

        mSceneCommunication->setBackgroundBrush(Qt::gray);

        mControlLayout->addWidget(mCommunicationView);
        QGraphicsRectItem *rectppal2= mSceneCommunication->addRect(0,0,1920-100,200);
        rectppal2->setBrush(Qt::blue);
        qWarning() << "Tamaño de rect principal" << rectppal2->rect();
        rectppal2->setPos(0,0);
        mCommunicationView->setScene(mSceneCommunication);
        mPecsWidget->setLayout(mControlLayout);
        qDebug()<<mSceneCommunication->sceneRect();



    //    mCentralView->show();
       //mSceneCommunication->addWidget(lineaComunicacion);

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
