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


#ifndef WNDNEWFIREFIGHTER_H
#define WNDNEWFIREFIGHTER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include "databasemanager.h"
#include "firefighter.h"

namespace Ui {
    class wndNewFirefighter;
}

class wndNewFirefighter : public QMainWindow {
    Q_OBJECT
public:
    wndNewFirefighter(QWidget *parent = 0, DatabaseManager *newDb=0);
    ~wndNewFirefighter();

private slots:
    void btnAdd_Clicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wndNewFirefighter *ui;
    DatabaseManager *db;
};

#endif // WNDNEWFIREFIGHTER_H