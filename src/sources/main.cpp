/*
    Fire Department Management System
    Copyright (C) 2010  Joseph W. Dougherty

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <QtGui/QApplication>
#include <QMessageBox>
#include <QString>
#include <QDateTime>
#include <QFontDatabase>
#include <QFile>

#include "../headers/LogFunctions.h"
#include "../headers/settingsmanager.h"
#include "../headers/databasemanager.h"
#include "../headers/mainwindow.h"
#include "../headers/wndsetup.h"

int main( int argc, char *argv[] )
{
    QApplication application( argc, argv );
    SettingsManager *pSM = SettingsInstance();
    DatabaseManager *pDB = DatabaseInstance();
    MainWindow mw( 0, pDB );

    //setupDebugRedirection();

    qDebug( "Initialized at %s", qPrintable( QDateTime::currentDateTime().toString() ) );

    QFile res( ":/fonts/FRE3OF9X.TTF" );
    if ( res.open( QIODevice::ReadOnly ) )
    {
        QFontDatabase::addApplicationFontFromData( res.readAll() );
    }
    else
    {
        qWarning( "Resource Error: Could not load Free 3 of 9 Extended barcode font." );
    }

    // Settings file DNE
    if ( !pSM->exists() )
    {
        wndSetup setup( 0, pDB, pSM, &mw );
        setup.show();
        qDebug( "Running program setup." );
        return application.exec();
    }

    pSM->load();
    pDB->setDBFile( pSM->getDBFile() );
    pDB->buildQueries();

    // DB file DNE
    if ( !pDB->exists() )
    {
        int iResult = QMessageBox::question( 0, "Database not found.", "Database could not be found. Run setup?",
                                             QMessageBox::Yes | QMessageBox::No );

        switch ( iResult )
        {
            case QMessageBox::Yes:
            {
                wndSetup setup( 0, pDB, pSM, &mw );
                setup.show();
                qDebug( "Running program setup." );
                return application.exec();
            }
            case QMessageBox::No:
            {
                QMessageBox::critical( 0, "Critical Error", "Startup cannnot continue. Closing program.", QMessageBox::Ok );
                qCritical( "Critical Error - Startup cannot continue." );
                return 0;
            }
            default:
            {
               QMessageBox::critical( 0, "Critical Error", "Default case reached.", QMessageBox::Ok );
               qCritical( "Critical Error - Default case reached." );
               return 0;
            }
        }
    }

    mw.showMaximized();

    if ( !pDB->open() )
    {
        QMessageBox::critical( &mw, "Critical Error", "Database could not be opened.", QMessageBox::Ok );
        qCritical( "Critical Error - Database: Could not be opened." );
        return 0;
    }

    if ( !pDB->verify() )
    {
        QMessageBox::critical( &mw, "Critical Error", "Database has an invalid structure.", QMessageBox::Ok );
        qCritical( "Critical Error - Database: Invalid structure." );
        return 0;
    }

    return application.exec();
}
