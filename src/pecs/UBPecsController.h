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

#ifndef UBPECSCONTROLLER_H_
#define UBPECSCONTROLLER_H_

#include <QObject>
#include "core/UBApplicationController.h"

/*namespace Ui
{
    class pecswindow;
}
*/
class UBPecsController : public QObject
{
    Q_OBJECT

    public:
        UBPecsController(UBMainWindow* mainWindow);
        virtual ~UBPecsController();

        void closing();

        void show();


    protected:
        void setupViews ();
    public slots:


    private:
        UBMainWindow *mMainWindow;
        //Ui::pecswindow* mPecsUI;
        QWidget *mPecsWidget;
        QHBoxLayout *mControlLayout;

        QGraphicsView *mCentralView;


    private slots:



    signals:

};


#endif /* UBPECSCONTROLLER_H_ */
