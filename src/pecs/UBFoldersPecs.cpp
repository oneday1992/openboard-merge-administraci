#include "UBFoldersPecs.h"
#include "globals/UBGlobals.h"
#include "gui/UBFeaturesWidget.h"

const char *UBFoldersPecs::objNamePathList = "PathList";
const char *UBFoldersPecs::objNameFeatureList = "FeatureList";

UBFoldersPecs::UBFoldersPecs(QWidget *parent, const char *name) : UBDockPaletteWidget(parent)
{
    setObjectName(name);
    mName = "FoldersPecs";
    mVisibleState = true;
    SET_STYLE_SHEET();

    mIconToLeft = QPixmap(":images/library_open.png");
    mIconToRight = QPixmap(":images/library_close.png");
    setAcceptDrops(true);

    //Main UBFeature functionality
    //controller = new UBFeaturesController(this);
    controller = new UBFeaturesFoldersPecsController(this); // Nueva clase par acontrolar Pecs
    //Main layout including all the widgets in palette
    layout = new QVBoxLayout(this);

    //Path icon view on the top of the palette
    pathListView = new UBFeaturesListView(this, objNamePathList);
    controller->assignPathListView(pathListView);

    centralWidget = new UBFeaturesCentralWidget(this);
    controller->assignFeaturesListView(centralWidget->listView());
    centralWidget->setSliderPosition(UBSettings::settings()->featureSliderPosition->get().toInt());

    //Bottom actionbar for DnD, quick search etc
    //mActionBar = new UBFeaturesActionBar(controller, this);

    //Filling main layout
    layout->addWidget(pathListView); //pathListView Navegacion de arriba de la paleta
    layout->addWidget(centralWidget); //Lista de carpetas de pecs
    //layout->addWidget(mActionBar);

    //Conectamos el click de un carpeta de pecs en el lista central o en la barra de navegación
    connect(centralWidget->listView(), SIGNAL(clicked(const QModelIndex &)), this, SLOT(currentSelected(const QModelIndex &)));
    connect(pathListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(currentSelected(const QModelIndex &)));

}

UBFoldersPecs::~UBFoldersPecs()
{
    if (controller)
        delete controller;
    if (layout)
        delete layout;
    if (pathListView)
        delete pathListView;
    if (centralWidget)
        delete centralWidget;
    if (mActionBar)
        delete mActionBar;


}

void UBFoldersPecs::currentSelected(const QModelIndex &current)
{
    if (!current.isValid()) {
           qWarning() << "SLOT:currentSelected, invalid index catched";
           return;
       }

       QString objName = sender()->objectName();

       if (objName.isEmpty()) {
           qWarning() << "incorrect sender";
       } else if (objName == objNamePathList) {
           //Calling to reset the model for listView. Maybe separate function needed
           controller->searchStarted("", centralWidget->listView());
       }

       UBFeature feature = controller->getFeature(current, objName);

       if ( feature.isFolder() ) {
           QString newPath = feature.getFullVirtualPath();

           controller->setCurrentElement(feature);
           controller->siftElements(newPath);

           centralWidget->switchTo(UBFeaturesCentralWidget::MainList);

           if ( feature.getType() == FEATURE_FAVORITE ) {
               //mActionBar->setCurrentState( IN_FAVORITE );

           }  else if ( feature.getType() == FEATURE_CATEGORY && feature.getName() == "root" ) {
               //mActionBar->setCurrentState( IN_ROOT );

           } else if (feature.getType() == FEATURE_TRASH) {
               //mActionBar->setCurrentState(IN_TRASH);

           } else if (feature.getType() == FEATURE_SEARCH) {
               //The search feature behavior is not standard. If features list clicked - show empty element
               //else show existing saved features search QWebView
               if (sender()->objectName() == objNameFeatureList) {
                   centralWidget->showElement(feature, UBFeaturesCentralWidget::FeaturesWebView);
               } else if (sender()->objectName() == objNamePathList) {
                   centralWidget->switchTo(UBFeaturesCentralWidget::FeaturesWebView);
               }

           } else  {
               //mActionBar->setCurrentState(IN_FOLDER);
           }

   //    } else if (feature.getType() == FEATURE_SEARCH) {
   //        centralWidget->showElement(feature, UBFeaturesCentralWidget::FeaturesWebView);

       } else {
           centralWidget->showElement(feature, UBFeaturesCentralWidget::FeaturePropertiesList);
           //mActionBar->setCurrentState( IN_PROPERTIES );
       }
       //mActionBar->cleanText();
}

