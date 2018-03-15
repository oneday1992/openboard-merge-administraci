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




#ifndef UBDOCKPALETTE_H
#define UBDOCKPALETTE_H

class UBDocumentProxy;

#include <QWidget>
#include <QMouseEvent>
#include <QBrush>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QEvent>
#include <QTime>
#include <QPoint>
#include <QPixmap>
#include <QMap>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QVector>

#include "UBDockPaletteWidget.h"

#define TABSIZE        50       //Height of the tab of the palette (Altura de la pestaña de la paleta)
#define CLICKTIME   1000000  //Clicktime to expand or collapse palette (Tiempo de click para expandir o colapsar la paleta)

/**
 * \brief The dock positions
 */
typedef enum
{
    eUBDockOrientation_Left,  /** Left dock (Izquierdo)*/
    eUBDockOrientation_Right, /** Right dock (Derecho)*/
    eUBDockOrientation_Top,   /** [to be implemented]Top dock (Arriba)*/
    eUBDockOrientation_Bottom /** [to be implemented]Bottom dock (Abajo)*/
}eUBDockOrientation;

typedef enum
{
    eUBDockTabOrientation_Up,   /** Up tabs */
    eUBDockTabOrientation_Down  /** Down tabs */
}eUBDockTabOrientation;

class UBDockPalette;

class UBTabDockPalette : public QWidget
{
    Q_OBJECT
    friend class UBDockPalette;

public:

    UBTabDockPalette(UBDockPalette *dockPalette, QWidget *parent = 0);
    ~UBTabDockPalette();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    UBDockPalette *dock;
    int mVerticalOffset;
    bool mFlotable;
};


typedef enum
{
    eUBDockPaletteType_LEFT,
    eUBDockPaletteType_RIGHT,
    eUBDockPaletteType_DOWN
} eUBDockPaletteType;


class UBDockPalette : public QWidget
{
    Q_OBJECT
    friend class UBTabDockPalette;

public:
    UBDockPalette(eUBDockPaletteType paletteType, QWidget* parent=0, const char* name="UBDockPalette");
    ~UBDockPalette();

    eUBDockOrientation orientation();
    void setOrientation(eUBDockOrientation orientation);
    void setTabsOrientation(eUBDockTabOrientation orientation);
    void showTabWidget(int tabIndex);
    QRect getTabPaletteRect();

    virtual void assignParent(QWidget *widget);
    virtual void setVisible(bool visible);

    virtual void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);

    void setBackgroundBrush(const QBrush& brush);
    void registerWidget(UBDockPaletteWidget* widget);

    void addTab(UBDockPaletteWidget* widget);
    void removeTab(UBDockPaletteWidget* widget);

    void connectSignals();

    bool switchMode(eUBDockPaletteWidgetMode mode);

    eUBDockPaletteWidgetMode mCurrentMode;

    QVector<UBDockPaletteWidget*> GetWidgetsList() { return mRegisteredWidgets; }

public:
    bool isTabFlotable() {return mTabPalette->mFlotable;}
    void setTabFlotable(bool newFlotable) {mTabPalette->mFlotable = newFlotable;}
    int getAdditionalVOffset() const {return mTabPalette->mVerticalOffset;}
    void setAdditionalVOffset(int newOffset) {mTabPalette->mVerticalOffset = newOffset;}

    eUBDockPaletteType paletteType(){return mPaletteType;}

public slots:
    void onShowTabWidget(UBDockPaletteWidget* widget);
    void onHideTabWidget(UBDockPaletteWidget* widget);
    void onAllDownloadsFinished();
    virtual void onDocumentSet(UBDocumentProxy* documentProxy);

signals:
    void mouseEntered();

protected:
    virtual int border();
    virtual int radius();
    virtual int customMargin();
    virtual void updateMaxWidth();
    virtual void resizeEvent(QResizeEvent *event);
    virtual int collapseWidth();

    /** The current dock orientation
    * La orientacion actual del dock
    */
    eUBDockOrientation mOrientation;
    /** The current background brush
    * El pincel de fondo actual
    */
    QBrush mBackgroundBrush;
    /** The preferred width
    * El ancho preferido
    */
    int mPreferredWidth;
    /** The preferred height
    * La altura preferida
    */
    int mPreferredHeight;
    /** A flag used to allow the resize
    * Bandera usada para permitir el cambio de tamaño
    */
    bool mCanResize;
    /** A flag indicating if the palette has been resized between a click and a release
    * Una bandera que indica si la paleta se ha cambiado de tamaño entre un clic y una version
    */
    bool mResized;
    /** The width that trig the collapse
    * El ancho que activa el colapso
    */
    int mCollapseWidth;
    /** The last width of the palette
    * El ultimo ancho de la paleta
    */
    int mLastWidth;
    /** The last height of the palette
    * El ultimo alto de la paleta
    */
    int mLastHeight;
    /** The click time
    * El tiempo de clic
    */
    QTime mClickTime;
    /** The mouse pressed position
    * La posicion presionada por el raton
    */
    QPoint mMousePressPos;
    /** The tab orientation
    * La orientacion de las pestañas
    */
    eUBDockTabOrientation mTabsOrientation;
    /** The h position of the tab
    * La posicion horizontal de la pestaña
    */
    int mHTab;
    /** The stacked widget
    * El widget apilado
    */
    QStackedWidget* mpStackWidget;
    /** The layout
    * El diseño
    */
    QVBoxLayout* mpLayout;
    /** The current tab index
    * El indice de la pestaña actual
    */
    int mCurrentTab;
    /** The visible tab widgets
    * El widget de pestañas visible
    */
    QVector<UBDockPaletteWidget*> mTabWidgets;
    /** The current widget
    * El widget actual
    */
    QVector<UBDockPaletteWidget*> mRegisteredWidgets;
    /** The current tab widget
    * El widget de pestaña actual
    */
    QString mCrntTabWidget;
    /** Last opened tab index depending on mode
    * El ultimo indice de pestaña abierto segun el modo
    */
    QMap<eUBDockPaletteWidgetMode,int> mLastOpenedTabForMode;

private slots:
    void onToolbarPosUpdated();
    void onResizeRequest(QResizeEvent* event);

private:
    void tabClicked(int tabIndex);
    int tabSpacing();
    void toggleCollapseExpand();
    void moveTabs();
    void resizeTabs();

private:
    eUBDockPaletteType mPaletteType;
    UBTabDockPalette *mTabPalette;
};

#endif // UBDOCKPALETTE_H
