#ifndef UBFOLDERSPECS_H
#define UBFOLDERSPECS_H

#include "gui/UBDockPaletteWidget.h"
#include "board/UBFeaturesController.h"
#include <QVBoxLayout>
#include "gui/UBFeaturesActionBar.h"
#include "gui/UBFeaturesWidget.h"


class UBFoldersPecs : public UBDockPaletteWidget
{
public:
    UBFoldersPecs(QWidget* parent=0, const char* name="UBFoldersPecs");
    ~UBFoldersPecs();

    bool visibleInMode(eUBDockPaletteWidgetMode mode)
        {
            return mode == eUBDockPaletteWidget_BOARD
                || mode == eUBDockPaletteWidget_DESKTOP;
        }
    static const char *objNamePathList;
    static const char *objNameFeatureList;

private:
    UBFeaturesController *controller;
    QVBoxLayout *layout;
    UBFeaturesListView *pathListView;
    UBFeaturesCentralWidget *centralWidget;
    UBFeaturesActionBar *mActionBar;


};

#endif // UBFOLDERSPECS_H
