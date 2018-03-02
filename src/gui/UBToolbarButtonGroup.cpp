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




#include "UBToolbarButtonGroup.h"

#include <QtGui>
#include <QLayout>
#include <QStyleOption>

#include "core/UBApplication.h"
#include "core/UBSettings.h"

#include "board/UBDrawingController.h"
#include "UBAbstractSubPalette.h"

#include "core/memcheck.h"

UBToolbarButtonGroup::UBToolbarButtonGroup(QToolBar *toolBar, const QList<QAction*> &actions, bool isColorToolBar)
    : QWidget(toolBar)
    , mActions(actions)
    , mCurrentIndex(-1)
    , mDisplayLabel(true)
    , mActionGroup(0)
    , launched(false)
{
    Q_ASSERT(actions.size() > 0);

    isColorTool = isColorToolBar;
    mToolButton = qobject_cast<QToolButton*>(toolBar->layout()->itemAt(0)->widget());
    Q_ASSERT(mToolButton);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    verticalLayout->addStretch();
    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addStretch();

    mActionGroup = new QActionGroup(this);
    mActionGroup->setExclusive(true);

    QSize buttonSize;

    int i = 0;

    foreach(QAction *action, actions)
    {
        mActionGroup->addAction(action);
        QToolButton *button = new QToolButton(this);
        mButtons.append(button);
        button->setDefaultAction(action);
        button->setCheckable(true);

        if(i == 0)
        {
            button->setObjectName("ubButtonGroupLeft");
        }
        else if (i == actions.size() - 1)
        {
            button->setObjectName("ubButtonGroupRight");
        }
        else
        {
            button->setObjectName("ubButtonGroupCenter");
        }

        if((isColorTool == true) && ((i+1) == UBSettings::colorPaletteSize )) // If it is the last color button, then it is the CUSTOM COLOR BUTTON
            connect(button, SIGNAL(clicked(bool)), this, SLOT(nuevoMethod()));

        connect(button, SIGNAL(triggered(QAction*)), this, SLOT(selected(QAction*)));

        horizontalLayout->addWidget(button);
        mLabel = action->text();
        buttonSize = button->sizeHint();
        i++;
    }

    if(isColorToolBar == true){
        // Issue 27/02/2018 - OpenBoard - CUSTOM COLOR.
        mColorDialog = new QColorDialog(this);
        mColorDialog->setOptions(QColorDialog::DontUseNativeDialog);

        connect(mColorDialog,SIGNAL(colorSelected(QColor)),this,SLOT(updateCustomColor(QColor)));
        // End - Issue 27/02/2018 - OpenBoard - CUSTOM COLOR.
    }
}

UBToolbarButtonGroup::~UBToolbarButtonGroup()
{
    // NOOP
}


// Issue 27/02/2018 - OpenBoard - CUSTOM COLOR.
void UBToolbarButtonGroup::updateCustomColor(QColor selectedColor){
    qWarning()<<"updateCustomColor";

    bool isDarkBackground = UBSettings::settings()->isDarkBackground();
    int i = UBSettings::colorPaletteSize - 1; // The last button is CUSTOM COLOR.
    if (UBDrawingController::drawingController()->stylusTool() == UBStylusTool::Pen
        || UBDrawingController::drawingController()->stylusTool() == UBStylusTool::Line)
    {
        if(isDarkBackground){
            UBSettings::settings()->boardPenDarkBackgroundSelectedColors->setColor(i,selectedColor);
            UBDrawingController::drawingController()->setPenColor(true,selectedColor,i);
        }
        else{
            UBSettings::settings()->boardPenLightBackgroundSelectedColors->setColor(i,selectedColor);
            UBDrawingController::drawingController()->setPenColor(false,selectedColor,i);
        }

    }
    else if (UBDrawingController::drawingController()->stylusTool() == UBStylusTool::Marker)
    {
        if(isDarkBackground){
            UBSettings::settings()->boardMarkerDarkBackgroundSelectedColors->setColor(i,selectedColor);
            UBDrawingController::drawingController()->setMarkerColor(true,selectedColor,i);
        }
        else{
            UBSettings::settings()->boardMarkerLightBackgroundSelectedColors->setColor(i,selectedColor);
            UBDrawingController::drawingController()->setMarkerColor(false,selectedColor,i);
        }
    }
    QPixmap px(12, 12);
    px.fill(selectedColor);
    mButtons.at(i)->setIcon(px);
}



void UBToolbarButtonGroup::setIcon(const QIcon &icon, int index)
{
    Q_ASSERT(index < mActions.size());

    foreach(QWidget *widget, mActions.at(index)->associatedWidgets())
    {
        QToolButton *button = qobject_cast<QToolButton*>(widget);
        if (button)
        {
            button->setIcon(icon);
        }
    }
}

void UBToolbarButtonGroup::setColor(const QColor &color, int index)
{
    QPixmap pixmap(12, 12);
    pixmap.fill(color);
    QIcon icon(pixmap);
    setIcon(icon, index);
}

// Issue Open-Board 27/02/2018 - Custom color choice
void UBToolbarButtonGroup::nuevoMethod(){
    mColorDialog->show(); // The color is updated once it is closed.
    mColorDialog->activateWindow();
    mColorDialog->raise();
}

void UBToolbarButtonGroup::selected(QAction *action)
{
    foreach(QWidget *widget, action->associatedWidgets())
    {
        QToolButton *button = qobject_cast<QToolButton*>(widget);
        if (button)
        {
            int i = 0;
            foreach(QAction *eachAction, mActions)
            {
                if (eachAction == action)
                {
                    setCurrentIndex(i);
                    emit activated(i);
                    break;
                }
                i++;
            }
        }
    }
}

int UBToolbarButtonGroup::currentIndex() const
{
    return mCurrentIndex;
}

void UBToolbarButtonGroup::setCurrentIndex(int index)
{    
    Q_ASSERT(index < mButtons.size());

    qWarning()<<mCurrentIndex;
    if (index != mCurrentIndex)
    {
        for(int i = 0; i < mButtons.size(); i++)
        {
            mButtons.at(i)->setChecked(i == index);
        }
        mCurrentIndex = index;
        qWarning()<<"currentIndexChanged(index)";
        emit currentIndexChanged(index);
    }
}

void UBToolbarButtonGroup::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QStyleOptionToolButton option;
    QPixmap emptyPixmap(32, 32);
    emptyPixmap.fill(Qt::transparent);
    QIcon emptyIcon(emptyPixmap);

    option.initFrom(mToolButton);

    option.text = mLabel;
    option.font = mToolButton->font();

    int pointSize = mToolButton->font().pointSize();
    if (pointSize > 0)
        option.font.setPointSize(pointSize);
    else
    {
        int pixelSize = mToolButton->font().pixelSize();
        if (pixelSize > 0)
            option.font.setPixelSize(pixelSize);
    }

    option.rect = rect();
    option.icon = emptyIcon; // non null icon is required for style()->drawControl(QStyle::CE_ToolButtonLabel, ...) to work correctly
    option.iconSize = emptyPixmap.size();
    option.toolButtonStyle = mDisplayLabel ? Qt::ToolButtonTextUnderIcon : Qt::ToolButtonIconOnly;

    style()->drawControl(QStyle::CE_ToolButtonLabel, &option, &painter, this);
}


void UBToolbarButtonGroup::colorPaletteChanged()
{
    bool isDarkBackground = UBSettings::settings()->isDarkBackground();

    QList<QColor> colors;

    if (UBDrawingController::drawingController()->stylusTool() == UBStylusTool::Pen 
        || UBDrawingController::drawingController()->stylusTool() == UBStylusTool::Line)
    {
        colors = UBSettings::settings()->penColors(isDarkBackground);
    }
    else if (UBDrawingController::drawingController()->stylusTool() == UBStylusTool::Marker)
    {
        colors = UBSettings::settings()->markerColors(isDarkBackground);
    }

    for (int i = 0; i < mButtons.size() && i < colors.size(); i++)
    {
        setColor(colors.at(i), i);
    }
}

void UBToolbarButtonGroup::displayText(QVariant display)
{
    mDisplayLabel = display.toBool();
    QVBoxLayout* verticalLayout = (QVBoxLayout*)layout();
    verticalLayout->setStretch(2, mDisplayLabel ? 1 : 0);
    update();
}
