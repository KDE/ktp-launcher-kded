/*
 * This file is part of KDE
 *
 * Copyright (C) 2009 Collabora Ltd. <http://www.collabora.co.uk/>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "kded-telepathy-launcher.h"

#include <KDebug>
#include <KPluginFactory>

#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusPendingCall>
#include <QtDBus/QDBusPendingCallWatcher>
#include <QtDBus/QDBusPendingReply>

K_PLUGIN_FACTORY(TelepathyLauncherFactory, registerPlugin<TelepathyLauncher>(); )
K_EXPORT_PLUGIN(TelepathyLauncherFactory("telepathy_launcher"))

TelepathyLauncher::TelepathyLauncher(QObject *parent, const QList<QVariant> &)
  : KDEDModule(parent),
    mc5Interface(0)
{
    kDebug() << "Badger Badger Mushroom...";

    // Get the DBus Interface for Mission Control, and prod it to make sure it is launched.
    mc5Interface = new QDBusInterface("org.freedesktop.Telepathy.MissionControl5",
                                      "/org/freedesktop/Telepathy/AccountManager",
                                      "org.freedesktop.DBus.Properties");

    QDBusPendingCall call =  mc5Interface->asyncCall("GetAll",
                                                        "org.freedesktop.Telepathy.AccountManager");

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);
    connect(watcher,
            SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(getAccountManagerPropertiesFinished(QDBusPendingCallWatcher*)));

}

TelepathyLauncher::~TelepathyLauncher()
{
    kDebug();

    mc5Interface->deleteLater();
}

void TelepathyLauncher::getAccountManagerPropertiesFinished(QDBusPendingCallWatcher *watcher)
{
    kDebug();

    QDBusPendingReply<QVariantMap> reply = *watcher;
     if (reply.isError()) {
         kDebug() << "Pending Reply error:" << reply.error();
     } else {
         kDebug() << "Pending Reply success.";
     }
}


#include "kded-telepathy-launcher.moc"

