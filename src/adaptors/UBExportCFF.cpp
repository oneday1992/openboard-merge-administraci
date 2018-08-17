/*
 * Copyright (C) 2010-2013 Groupement d'Intérêt Public pour l'Education Numérique en Afrique (GIP ENA)
 *
 * This file is part of Open-Sankoré.
 *
 * Open-Sankoré is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * Open-Sankoré is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open-Sankoré.  If not, see <http://www.gnu.org/licenses/>.
 */



#include "UBExportCFF.h"
#include "UBCFFAdaptor.h"
#include "document/UBDocumentProxy.h"
#include "core/UBDocumentManager.h"
#include "core/UBApplication.h"
#include "core/memcheck.h"
#include "document/UBDocumentController.h"

#include <QModelIndex>
#include <QObject>


UBExportCFF::UBExportCFF(QObject *parent)
: UBExportAdaptor(parent)
{

}

UBExportCFF::~UBExportCFF()
{

}
QString UBExportCFF::exportName()
{
    return tr("Export to IWB");
}

QString UBExportCFF::exportExtention()
{
    return QString(".iwb");
}

void UBExportCFF::persist(UBDocumentProxy* pDocument)
{
    QString src = pDocument->persistencePath();

    if (!pDocument)
        return;

    QString filename = askForFileName(pDocument, tr("Export as IWB File"));

    if (filename.length() > 0)
    {
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        if (mIsVerbose)
            UBApplication::showMessage(tr("Exporting document..."));

            UBCFFAdaptor toIWBExporter;
            if (toIWBExporter.convertUBZToIWB(src, filename))
            {
                if (mIsVerbose)
                    UBApplication::showMessage(tr("Export successful."));
            }
            else 
                if (mIsVerbose)
                    UBApplication::showMessage(tr("Export failed."));

        showErrorsList(toIWBExporter.getConversionMessages());

        QApplication::restoreOverrideCursor();

    }

    
}

bool UBExportCFF::associatedActionactionAvailableFor(const QModelIndex &selectedIndex)
{
    /*const UBDocumentTreeModel *docModel = qobject_cast<const UBDocumentTreeModel*>(selectedIndex.model());
    if (!selectedIndex.isValid() || docModel->isCatalog(selectedIndex)) {
        return false;
    }*/

    return true;
}
