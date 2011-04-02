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

#include "managers/PluginManager.h"

PluginManager* getPluginManager( void )
{
    static PluginManager db;
    return &db;
}

PluginManager::PluginManager( void )
{
    _sFolder = QString::null;
}

PluginManager::~PluginManager( void )
{

}

bool PluginManager::initialize( void )
{
    SettingManager *sm = getSettingManager();
    _sFolder = sm->get( "plugins/folder" ).toString();

    if ( !exists() ) return false;

    return true;
}

bool PluginManager::setFolder( QString sFolder )
{
    SettingManager *sm = getSettingManager();
    sm->set( "plugins/folder", sFolder );

    return initialize();
}

//! See if the folder exists.
/*!
  \return bool - Plugin folder exists.
*/
bool PluginManager::exists( void )
{
    if ( _sFolder == QString::null || !QDir( _sFolder ).exists() )
    {
        qDebug( qPrintable( QObject::tr( "PluginManager: %s folder does not exist." ) ), qPrintable( _sFolder ) );
        return false;
    }

    qDebug( qPrintable( QObject::tr( "PluginManager: %s folder exists." ) ), qPrintable( _sFolder ) );
    return true;
}

bool PluginManager::load( void )
{
    QDir pluginsDir( _sFolder );

    qDebug( qPrintable( QObject::tr( "PluginManager: Loading plugins." ) ) );

#if defined( Q_OS_WIN )
    if ( pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release" )
    {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#elif defined( Q_OS_MAC )
    if ( pluginsDir.dirName() == "MacOS" )
    {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif

    pluginsDir.cd( "plugins" );

    lDatabasePlugins.clear();
    lMDIWindowPlugins.clear();

    foreach ( QString sFileName, pluginsDir.entryList( QDir::Files ) )
    {
        QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( sFileName ) );
        QObject *plugin = pluginLoader.instance();

        if ( plugin )
        {
            DatabasePlugin *databasePlugin = qobject_cast<DatabasePlugin*>( plugin );
            MDIWindowPlugin *mdiWindowPlugin = qobject_cast<MDIWindowPlugin*>( plugin );

            if ( databasePlugin )
            {
                lDatabasePlugins.append( databasePlugin );
                lPlugins.append( ( BasePlugin* )databasePlugin );
            }
            else if ( mdiWindowPlugin )
            {
                lMDIWindowPlugins.append( mdiWindowPlugin );
                lPlugins.append( ( BasePlugin* )mdiWindowPlugin );
            }
        }
    }
    return true;
}

QStringList PluginManager::findPlugins( QString sFolder )
{
    QDir pluginsDir( sFolder );
    QStringList plugins;

    foreach ( QString sFileName, pluginsDir.entryList( QDir::Files ) )
    {
        QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( sFileName ) );
        QObject *plugin = pluginLoader.instance();

        if ( plugin )
        {
            DatabasePlugin *databasePlugin = qobject_cast<DatabasePlugin*>( plugin );
            MDIWindowPlugin *mdiWindowPlugin = qobject_cast<MDIWindowPlugin*>( plugin );

            if ( databasePlugin || mdiWindowPlugin )
            {
                plugins.append( sFileName );
            }
        }
    }
    return plugins;
}