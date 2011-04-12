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

#ifndef CALLPLUGIN_H
#define CALLPLUGIN_H

#include <QObject>
#include <QtCore/QtPlugin>

#include "plugins/DatabasePlugin.h"
#include "plugins/DependencyList.h"
#include "plugins/PluginInfo.h"

class CallPlugin : public QObject, DatabasePlugin
{
    Q_OBJECT
    Q_INTERFACES( DatabasePlugin )

    public:
        PluginInfo                  getInfo( void );
        DependencyList              getDependencies( void );

        QString                     echo( const QString &message );
};

#endif // FIREFIGHTERPLUGIN_H