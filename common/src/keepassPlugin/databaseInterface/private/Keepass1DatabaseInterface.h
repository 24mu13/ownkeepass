/***************************************************************************
**
** Copyright (C) 2012 - 2015 Marko Koschak (marko.koschak@tisno.de)
** All rights reserved.
**
** This file is part of ownKeepass.
**
** ownKeepass is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** ownKeepass is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with ownKeepass.  If not, see <http://www.gnu.org/licenses/>.
**
***************************************************************************/

#ifndef KEEPASS1DATABASEINTERFACE_H
#define KEEPASS1DATABASEINTERFACE_H

#include <QObject>
#include "AbstractDatabaseInterface.h"
#include "../KdbDatabase.h"
#include "../KdbListModel.h"
#include "database/Kdb3Database.h"

using namespace kpxPublic;

namespace kpxPrivate {

class Keepass1DatabaseInterface : public QObject, public AbstractDatabaseInterface
{
    Q_OBJECT
    Q_INTERFACES(AbstractDatabaseInterface)

public:
    explicit Keepass1DatabaseInterface(QObject* parent = 0);
    virtual ~Keepass1DatabaseInterface();

signals:
    // signals to all objects
    void disconnectAllClients();

    // signals to KdbDatabase object
    void databaseOpened(int result,
                        QString errorMsg);
    void newDatabaseCreated();
    void databaseClosed();
    void passwordChanged();
    void databaseSettingsChanged(int cryptAlgo, int kdf, int rounds);
    void errorOccured(int result,
                      QString errorMsg);

    // signals to KdbListModel object
    void appendItemToListModel(QString title,
                               QString iconUuid,
                               QString subTitle,
                               QString itemId,
                               int itemType,
                               int itemLevel,
                               QString modelId);
    void addItemToListModelSorted(QString title,
                                  QString iconUuid,
                                  QString subTitle,
                                  QString itemId,
                                  int itemType,
                                  int itemLevel,
                                  QString modelId);
    void updateItemInListModel(QString title,
                               QString iconUuid,
                               QString subTitle,
                               QString itemId,
                               QString modelId);
    void updateItemInListModelSorted(QString title,
                                     QString iconUuid,
                                     QString subTitle,
                                     QString itemId,
                                     QString modelId);
    void masterGroupsLoaded(int result,
                            QString errorMsg);
    void groupsAndEntriesLoaded(int result,
                                QString errorMsg);
    void deleteItemInListModel(QString itemId);
    void searchEntriesCompleted(int result,
                                QString errorMsg);

    // signal to KdbEntry object
    void entryLoaded(int result,
                     QString errorMsg,
                     QString entryId,
                     QStringList keys,
                     QStringList values,
                     QString iconUuid);
    void entrySaved(int result,
                    QString errorMsg,
                    QString entryId);
    void newEntryCreated(int result,
                         QString errorMsg,
                         QString entryId);
    void entryDeleted(int result,
                      QString errorMsg,
                      QString entryId);
    void entryMoved(int result,
                    QString errorMsg,
                    QString entryId);

    // signal to KdbGroup object
    void groupLoaded(int result,
                     QString errorMsg,
                     QString groupId,
                     QString title,
                     QString notes,
                     QString iconUuid);
    void groupSaved(int result,
                    QString errorMsg,
                    QString groupId);
    void newGroupCreated(int result,
                         QString errorMsg,
                         QString groupId);
    void groupDeleted(int result,
                      QString errorMsg,
                      QString groupId);
    void groupMoved(int result,
                    QString errorMsg,
                    QString groupId);

    // signal to KeepassIcon
    void appendCustomIconToListModel(QString uuid);

public slots:
    // signals from KdbDatabase object
    void slot_openDatabase(QString filePath,
                           QString password,
                           QString keyfile,
                           bool readonly);
    void slot_createNewDatabase(QString filePath,
                                QString password,
                                QString keyfile,
                                int cryptAlgorithm,
                                int keyTransfRounds);
    void slot_closeDatabase();
    void slot_changePassKey(QString password,
                            QString keyFile);
    void slot_changeDatabaseSettings(int cryptAlgo, int kdf, int rounds);
    void slot_setting_showUserNamePasswordsInListView(bool value) { m_setting_showUserNamePasswordsInListView = value; }
    void slot_setting_sortAlphabeticallyInListView(bool value) { m_setting_sortAlphabeticallyInListView = value; }

    // signal from KdbListModel object
    void slot_loadMasterGroups(bool registerListModel);
    void slot_loadGroupsAndEntries(QString groupId);
    void slot_unregisterListModel(QString modelId);
    void slot_searchEntries(QString searchString,
                            QString rootGroupId);

    // signal from KdbEntry object
    void slot_loadEntry(QString entryId);
    void slot_saveEntry(QString entryId,
                        QStringList keys,
                        QStringList values,
                        QStringList keysToDelete,
                        QStringList keysToRename,
                        QString iconUuid);
    void slot_createNewEntry(QStringList keys,
                             QStringList values,
                             QString parentGroupId,
                             QString iconUuid);
    void slot_deleteEntry(QString entryId);
    void slot_moveEntry(QString entryId,
                        QString newGroupId);

    // signal from KdbGroup object
    void slot_loadGroup(QString groupId);
    void slot_saveGroup(QString groupId,
                        QString title,
                        QString notes,
                        QString iconUuid);
    void slot_createNewGroup(QString title,
                             QString notes,
                             QString parentGroupId,
                             QString iconUuid);
    void slot_deleteGroup(QString groupId);
    void slot_moveGroup(QString groupId,
                        QString newParentGroupId);

    // signal from KeepassIcon
    void slot_loadCustomIcons();

public:
    const QImage getCustomIcon(const QString value);

private:
    void initDatabase();
    void updateGrandParentGroupInListModel(IGroupHandle* parentGroup);
    inline QString getUserAndPassword(IEntryHandle* entry);
    inline QString uInt2QString(uint value);
    inline uint qString2UInt(QString value);
    QString getEntryIcon(quint32 standardIcon);
    QString getGroupIcon(quint32 standardIcon);
    int UuidToIconNumber(QString value);

private:
    // Keepass database handler
    Kdb3Database* m_kdb3Database;

    // settings
    bool m_setting_showUserNamePasswordsInListView;
    bool m_setting_sortAlphabeticallyInListView;

    // The following two hash tables store information about which list models are showing a dedicated entry or group in the UI
    QHash<int, int> m_entries_modelId;
    QHash<int, int> m_groups_modelId;
    int m_rootGroupId;
};

}
#endif // KEEPASS1DATABASEINTERFACE_H
