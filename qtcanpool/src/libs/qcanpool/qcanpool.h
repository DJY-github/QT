/***************************************************************************
 **
 **  Copyright (C) 2018 MaMinJie <canpool@163.com>
 **  Contact: https://github.com/canpool
 **
 **  This program is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program.  If not, see http://www.gnu.org/licenses/.
 **
****************************************************************************/
#ifndef QCANPOOL_H
#define QCANPOOL_H

#include <QObject>
#include "qcanpool_global.h"

class QCANPOOL_SHARED_EXPORT QCanpool
{
public:
    /// color
    static QColor argbToColor(const QString &argb);
    static QString colorToArgb(const QColor &color); /// ffaabbcc

    // file
    static void showInExplorer(QString fileName);

    // settings
    static void setSysSettings(const QString &organization, const QString &application);
};

#endif // QCANPOOL_H
