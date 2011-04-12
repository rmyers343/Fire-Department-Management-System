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

#include "wndFirefighterPlugin.h"

PluginInfo wndCallPlugin::getInfo( void )
{
    return PluginInfo( "wndFirefighter", "0.01" );
}

DependencyList wndCallPlugin::getDependencies( void )
{
    DependencyList dependencies;
    dependencies.add( PluginInfo( "Firefighter", "0.01" ) );
    return dependencies;
}

void wndCallPlugin::menuBar( QMenu *pMenuBar )
{
    QIcon icon;
    icon.addFile( QString::fromUtf8( ":/icons/AddFirefighter.png" ), QSize(), QIcon::Normal, QIcon::Off );
    pMenuBar->addAction( icon, tr( "Add Firefighter" ) );
}

MDIWindow* wndCallPlugin::getInstance( QWidget *pParent, QMdiArea *pMDIArea )
{
    wndFirefighter *pWindow = new wndFirefighter( pParent, ((DatabaseObjectPlugin*)_Dependencies[0])->getInstance() );
    pMDIArea->addSubWindow( pWindow );
    return pWindow;
}

Q_EXPORT_PLUGIN2( wndfirefighter, wndCallPlugin );
