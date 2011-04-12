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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QByteArray>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QList>
#include <QObject>
#include <QPluginLoader>

#include "database_objects/Plugin.h"
#include "plugins/BasePlugin.h"
#include "plugins/DatabaseObjectPlugin.h"
#include "plugins/MDIWindowPlugin.h"
#include "managers/SettingManager.h"

class PluginManager
{
    private:
                                    PluginManager( void );
                                    ~PluginManager( void );

        QString                     getPluginHash( QString sFileName );

        QString                     _sFolder; //!< Plugin folder path.

    public:
        friend PluginManager*       getPluginManager( void );

        static QList<BasePlugin*>   findAll( QString sFolder );

        bool                        initialize( void );
        bool                        setFolder( QString sFolder );

        bool                        exists( void );

        bool                        install( QList<PluginInfo> lInstallThesePlugins );
        bool                        load( void );

        DatabaseObjectPlugin*             getDatabaseObjectPlugin( QString sName );
        MDIWindowPlugin*            getMDIWindowPlugin( QString sName );

        QList<BasePlugin*>          lPlugins;
        QList<DatabaseObjectPlugin*> lDatabaseObjectPlugins;
        QList<MDIWindowPlugin*>     lMDIWindowPlugins;
};

PluginManager* getPluginManager( void );

#endif // PLUGINMANAGER_H
