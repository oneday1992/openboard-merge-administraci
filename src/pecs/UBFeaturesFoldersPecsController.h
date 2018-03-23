#ifndef UBFEATURESFOLDERSPECSCONTROLLER_H
#define UBFEATURESFOLDERSPECSCONTROLLER_H
#include <QObject>
#include "board/UBFeaturesController.h"
#include "gui/UBFeaturesWidget.h"


/*
 *
 * Replica de UBFeaturesController
 *
 *
 */

class UBFeaturesFoldersPecsController : public QObject
{

    friend class UBFeaturesWidget;
    friend class UBFoldersPecs;

    Q_OBJECT

public:
    UBFeaturesFoldersPecsController(QWidget *parentWidget);
    virtual ~UBFeaturesFoldersPecsController();




        QList <UBFeature>* getFeatures() const {return featuresList;}

        const QString& getRootPath()const {return rootPath;}
    void scanFS();

        void addItemToPage(const UBFeature &item);
        void addItemAsBackground(UBFeature &item, bool isFromPalette);
        const UBFeature& getCurrentElement()const {return currentElement;}
        void setCurrentElement( const UBFeature &elem ) {currentElement = elem;}
        const UBFeature & getTrashElement () const { return trashElement; }

        void addDownloadedFile( const QUrl &sourceUrl, const QByteArray &pData, const QString pContentSource, const QString pTitle );

        UBFeature moveItemToFolder( const QUrl &url, const UBFeature &destination );
        UBFeature copyItemToFolder( const QUrl &url, const UBFeature &destination );
        void moveExternalData(const QUrl &url, const UBFeature &destination);

        void rescanModel();
    void siftElements(const QString &pSiftValue);
        //TODO make less complicated for betteer maintainence
    UBFeature getFeature(const QModelIndex &index, const QString &listName);
    void searchStarted(const QString &pattern, QListView *pOnView);
        void refreshModels();

        void deleteItem( const QUrl &url );
        void deleteItem(const UBFeature &pFeature);
        bool isTrash( const QUrl &url );
        void moveToTrash(UBFeature feature, bool deleteManualy = false);
        void addToFavorite( const QUrl &path );
        void removeFromFavorite(const QUrl &path, bool deleteManualy = false);
        void importImage(const QImage &image, const QString &fileName = QString());
        void importImage( const QImage &image, const UBFeature &destination, const QString &fileName = QString() );
        QStringList getFileNamesInFolders();

        void fileSystemScan(const QUrl &currPath, const QString & currVirtualPath);
        int featuresCount(const QUrl &currPath);
        static UBFeatureElementType fileTypeFromUrl( const QString &path );

        static QString fileNameFromUrl( const QUrl &url );
        static QImage getIcon( const QString &path, UBFeatureElementType pFType );
        static bool isDeletable( const QUrl &url );
        static char featureTypeSplitter() {return ':';}
        static QString categoryNameForVirtualPath(const QString &str);

        static const QString virtualRootName;

    void assignFeaturesListView(UBFeaturesListView *pList);
    void assignPathListView(UBFeaturesListView *pList);

public:
    static const QString startPath;
    static const QString toysPath;
    static const QString foodsPath;
    static const QString hygienePath;


    static const QString rootPath;
        static const QString audiosPath;
        static const QString moviesPath;
        static const QString picturesPath;
        static const QString appPath;
        static const QString flashPath;
        static const QString shapesPath;
        static const QString interactPath;
        static const QString trashPath;
        static const QString favoritePath;
        static const QString webSearchPath;

signals:
    void maxFilesCountEvaluated(int pLimit);
    void scanStarted();
    void scanFinished();
    void featureAddedFromThread();
    void scanCategory(const QString &);
    void scanPath(const QString &);

private slots:
        //void addNewFolder(QString name);
    void startThread();
        //void createNpApiFeature(const QString &str);

private:

        UBFeaturesItemDelegate *itemDelegate;
        UBFeaturesPathItemDelegate *pathItemDelegate;

    UBFeaturesModel *featuresModel;
    UBFeaturesProxyModel *featuresProxyModel;
    UBFeaturesSearchProxyModel *featuresSearchModel;
    UBFeaturesPathProxyModel *featuresPathModel;

        QAbstractItemModel *curListModel;
    UBFeaturesComputingThread mCThread;

private:

        static QImage createThumbnail(const QString &path);
        //void addImageToCurrentPage( const QString &path );
    void loadFavoriteList();
        void saveFavoriteList();
        QString uniqNameForFeature(const UBFeature &feature, const QString &pName = "Imported", const QString &pExtention = "") const;
        QString adjustName(const QString &str);

    QList <UBFeature> *featuresList;


        QString libraryPath;

    QUrl mLibStartDirectoryPath;
    QUrl mLibToysDirectoryPath;
    QUrl mLibFoodsDirectoryPath;
    QUrl mLibHygieneDirectoryPath;

        QUrl trashDirectoryPath;
        QUrl mLibSearchDirectoryPath;



        int mLastItemOffsetIndex;
        UBFeature currentElement;

    UBFeature startElement;
    UBFeature toysElement;
    UBFeature foodsElement;
    UBFeature hygieneElement;

    UBFeature rootElement;
        UBFeature favoriteElement;
        UBFeature audiosElement;
        UBFeature moviesElement;
        UBFeature picturesElement;
        UBFeature interactElement;
        UBFeature applicationsElement;
        UBFeature flashElement;
        UBFeature shapesElement;
        UBFeature webSearchElement;

    QSet <QUrl> *favoriteSet;

    public:
        UBFeature trashElement;
        UBFeature getDestinationFeatureForUrl( const QUrl &url );
        UBFeature getDestinationFeatureForMimeType(const QString &pMmimeType);





};

#endif // UBFEATURESFOLDERSPECSCONTROLLER_H
