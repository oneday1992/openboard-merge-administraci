#include "UBFeaturesFoldersPecsController.h"
#include "core/UBSettings.h"
#include "board/UBBoardController.h"
#include "tools/UBToolsManager.h"

const QString UBFeaturesFoldersPecsController::virtualRootName = "root";
const QString UBFeaturesFoldersPecsController::rootPath  = "/" + virtualRootName;

const QString UBFeaturesFoldersPecsController::startPath = rootPath + "/Start";
const QString UBFeaturesFoldersPecsController::toysPath = rootPath + "/Toys";
const QString UBFeaturesFoldersPecsController::foodsPath = rootPath + "/Foods";
const QString UBFeaturesFoldersPecsController::hygienePath = rootPath + "/Hygiene";




UBFeaturesFoldersPecsController::UBFeaturesFoldersPecsController(QWidget *parentWidget) : QObject(parentWidget)
    ,featuresList(0)
    ,mLastItemOffsetIndex(0)
{
    //Inicializo directorios físicos de UBSettings
    mLibStartDirectoryPath = QUrl::fromLocalFile(UBSettings::settings()->pecsStartDirectory());
    mLibToysDirectoryPath = QUrl::fromLocalFile(UBSettings::settings()->pecsToysDirectory());
    mLibFoodsDirectoryPath = QUrl::fromLocalFile(UBSettings::settings()->pecsFoodsDirectory());
    mLibHygieneDirectoryPath = QUrl::fromLocalFile(UBSettings::settings()->pecsHygieneDirectory());

    rootElement = UBFeature(rootPath, QImage( ":images/libpalette/home.png" ), "root", QUrl());
    startElement = UBFeature( startPath, QImage(":images/libpalette/start.svg"), tr("Inicio") , mLibStartDirectoryPath, FEATURE_CATEGORY);
    toysElement = UBFeature( toysPath, QImage(":images/libpalette/toys.svg"), tr("Juguetes") , mLibToysDirectoryPath, FEATURE_CATEGORY);
    foodsElement = UBFeature( foodsPath, QImage(":images/libpalette/foods.svg"), tr("Alimentos") , mLibFoodsDirectoryPath, FEATURE_CATEGORY);
    hygieneElement = UBFeature( hygienePath, QImage(":images/libpalette/hygiene.svg"), tr("Higiene") , mLibHygieneDirectoryPath, FEATURE_CATEGORY);

    featuresList = new QList <UBFeature>();
    scanFS();

    featuresModel = new UBFeaturesModel(featuresList, this);

    featuresProxyModel = new UBFeaturesProxyModel(this);
    featuresProxyModel->setFilterFixedString(rootPath);
    featuresProxyModel->setSourceModel(featuresModel);
    featuresProxyModel->setFilterCaseSensitivity( Qt::CaseInsensitive );

    featuresSearchModel = new UBFeaturesSearchProxyModel(this);
    featuresSearchModel->setSourceModel(featuresModel);
    featuresSearchModel->setFilterCaseSensitivity( Qt::CaseInsensitive );

    featuresPathModel = new UBFeaturesPathProxyModel(this);
    featuresPathModel->setPath(rootPath);
    featuresPathModel->setSourceModel(featuresModel);

        connect(featuresModel, SIGNAL(dataRestructured()), featuresProxyModel, SLOT(invalidate()));
        connect(&mCThread, SIGNAL(sendFeature(UBFeature)), featuresModel, SLOT(addItem(UBFeature)));
        connect(&mCThread, SIGNAL(featureSent()), this, SIGNAL(featureAddedFromThread()));
        connect(&mCThread, SIGNAL(scanStarted()), this, SIGNAL(scanStarted()));
        connect(&mCThread, SIGNAL(scanFinished()), this, SIGNAL(scanFinished()));
        connect(&mCThread, SIGNAL(maxFilesCountEvaluated(int)), this, SIGNAL(maxFilesCountEvaluated(int)));
        connect(&mCThread, SIGNAL(scanCategory(QString)), this, SIGNAL(scanCategory(QString)));
        connect(&mCThread, SIGNAL(scanPath(QString)), this, SIGNAL(scanPath(QString)));
        //connect(UBApplication::boardController, SIGNAL(npapiWidgetCreated(QString)), this, SLOT(createNpApiFeature(QString)));

        QTimer::singleShot(0, this, SLOT(startThread()));

}

UBFeaturesFoldersPecsController::~UBFeaturesFoldersPecsController()
{
    if (featuresList){
            delete featuresList;
    }
}

void UBFeaturesFoldersPecsController::scanFS()
{
    featuresList->clear();
    featuresList->append(rootElement);

    *featuresList << startElement
                   << toysElement
                   << foodsElement
                   << hygieneElement;

        //filling favoriteList
        loadFavoriteList(); // Hace falta implementar carpeta favorito
/*
        QList <UBToolsManager::UBToolDescriptor> tools = UBToolsManager::manager()->allTools();

        foreach (UBToolsManager::UBToolDescriptor tool, tools) {
            featuresList->append(UBFeature(appPath + "/" + tool.label, tool.icon.toImage(), tool.label, QUrl(tool.id), FEATURE_INTERNAL));
            if (favoriteSet->find(QUrl(tool.id)) != favoriteSet->end()) {
                featuresList->append(UBFeature(favoritePath + "/" + tool.label, tool.icon.toImage(), tool.label, QUrl(tool.id), FEATURE_INTERNAL));
            }
        }
*/
}

void UBFeaturesFoldersPecsController::siftElements(const QString &pSiftValue)
{
    featuresProxyModel->setFilterFixedString(pSiftValue);
    featuresProxyModel->invalidate();

    featuresPathModel->setPath(pSiftValue);
    featuresPathModel->invalidate();
}

UBFeature UBFeaturesFoldersPecsController::getFeature(const QModelIndex &index, const QString &listName)
{
    //    QSortFilterProxyModel *model = qobject_cast<QSortFilterProxyModel *>(pOnView->model());
    QAbstractItemModel *model = 0;
    if (listName == UBFeaturesWidget::objNamePathList) {
        model = featuresPathModel;
    } else if (listName == UBFeaturesWidget::objNameFeatureList) {
        model = curListModel;
    }

    if (model) {
        return model->data(index, Qt::UserRole + 1).value<UBFeature>();
    }

    return UBFeature();
    //    return pOnView->model()->data(index, Qt::UserRole + 1).value<UBFeature>();  /*featuresSearchModel->data(index, Qt::UserRole + 1).value<UBFeature>()*/;
}

void UBFeaturesFoldersPecsController::searchStarted(const QString &pattern, QListView *pOnView)
{
    if (pattern.isEmpty()) {

       pOnView->setModel(featuresProxyModel);
       featuresProxyModel->invalidate();
       curListModel = featuresProxyModel;
    } else if ( pattern.size() > 1 ) {

       //        featuresSearchModel->setFilterPrefix(currentElement.getFullVirtualPath());
       featuresSearchModel->setFilterWildcard( "*" + pattern + "*" );
       pOnView->setModel(featuresSearchModel );
       featuresSearchModel->invalidate();
       curListModel = featuresSearchModel;
    }
}

void UBFeaturesFoldersPecsController::assignFeaturesListView(UBFeaturesListView *pList)
{
    pList->setDragDropMode( QAbstractItemView::DragDrop );
    pList->setSelectionMode( QAbstractItemView::ContiguousSelection );

    pList->setResizeMode( QListView::Adjust );
    pList->setViewMode( QListView::IconMode );

    pList->setIconSize(QSize(UBFeaturesWidget::defaultThumbnailSize, UBFeaturesWidget::defaultThumbnailSize));
    pList->setGridSize(QSize(UBFeaturesWidget::defaultThumbnailSize + 20, UBFeaturesWidget::defaultThumbnailSize + 20));

    itemDelegate = new UBFeaturesItemDelegate(this, pList);
    pList->setItemDelegate(itemDelegate);

    pList->setModel(featuresProxyModel);
    curListModel = featuresProxyModel;
}

void UBFeaturesFoldersPecsController::assignPathListView(UBFeaturesListView *pList)
{
    pList->setViewMode(QListView::IconMode );
    pList->setIconSize(QSize(UBFeaturesWidget::defaultThumbnailSize - 10, UBFeaturesWidget::defaultThumbnailSize - 10));
    pList->setGridSize(QSize(UBFeaturesWidget::defaultThumbnailSize + 10, UBFeaturesWidget::defaultThumbnailSize - 10));
    pList->setFixedHeight(60);
    pList->setSelectionMode(QAbstractItemView::NoSelection);
    pList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pList->setFlow(QListView::LeftToRight);
    pList->setWrapping(false);
    pList->setDragDropMode(QAbstractItemView::DropOnly);

    pList->setModel( featuresPathModel);

    pathItemDelegate = new UBFeaturesPathItemDelegate(this);
    pList->setItemDelegate(pathItemDelegate);
}

void UBFeaturesFoldersPecsController::startThread()
{
    QList<QPair<QUrl, UBFeature> > computingData;

    computingData << QPair<QUrl, UBFeature>(mLibStartDirectoryPath, startElement)
            <<  QPair<QUrl, UBFeature>(mLibToysDirectoryPath, toysElement)
            <<  QPair<QUrl, UBFeature>(mLibFoodsDirectoryPath, foodsElement)
            <<  QPair<QUrl, UBFeature>(mLibHygieneDirectoryPath, hygieneElement);

        mCThread.compute(computingData, favoriteSet);

}


void UBFeaturesFoldersPecsController::loadFavoriteList()
{

    favoriteSet = new QSet<QUrl>();
    QFile file( UBSettings::userDataDirectory() + "/favoritesPecs.dat" );
    if ( file.exists() )
    {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        int elementsNumber;
        in >> elementsNumber;
        for ( int i = 0; i < elementsNumber; ++i)
        {
            QUrl path;
            in >> path;
            favoriteSet->insert( path );
        }
    }

}
