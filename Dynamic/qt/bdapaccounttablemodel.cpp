// Copyright (c) 2016-2021 Duality Blockchain Solutions Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bdapaccounttablemodel.h"

#include "bdappage.h"
#include "guiconstants.h"
#include "guiutil.h"
#include "rpc/client.h"
#include "rpc/register.h"
#include "rpc/server.h"
#include "sync.h"
#include "utiltime.h"
#include "validation.h" // for cs_main

#include <QDebug>
#include <QList>
#include <QTimer>
#include <QTableWidget>

#include <boost/algorithm/string.hpp>

// private implementation
class BdapAccountTablePriv
{
public:
    /** Local cache of peer information */
    QList<CAccountStats> cachedAccountStats;
    /** Column to sort nodes by */
    int sortColumn;
    /** Order (ascending or descending) to sort nodes by */
    Qt::SortOrder sortOrder;

    /** Populate tableWidget_Users via RPC call */
    void refreshAccounts(QTableWidget* inputtable, QLabel* statusDisplay, bool filterOn = false, std::string searchCommon = "", std::string searchPath = "", bool locked = true)
    {
        JSONRPCRequest jreq;
        std::vector<std::string> params;
        int nNewRow = 0;
        int recordsFound = 0;
    
        std::string keyName {""};
        std::string getName {""};
        std::string getPath {""};
        std::string getExpirationDate {""};
        std::string tableWidgetName {""};
        std::string outputmessage = "";
        bool hasValues = false;

        if (!inputtable->objectName().isEmpty()) tableWidgetName = inputtable->objectName().toStdString();

        //check if table has been previously sorted
        if (!inputtable->objectName().isEmpty()){
            if (inputtable->rowCount() > 0) {
                hasValues = true;
                sortColumn = inputtable->horizontalHeader()->sortIndicatorSection();
                sortOrder = inputtable->horizontalHeader()->sortIndicatorOrder();
            } //if rowcount
        } //if not isempty

        //Execute proper RPC call 
        if (tableWidgetName == "tableWidget_Groups") {
            if (filterOn) {
                params.push_back("groups");
                jreq.params = RPCConvertValues("mybdapaccounts", params);
                jreq.strMethod = "mybdapaccounts";
            } else {
                jreq.params = RPCConvertValues("getgroups", params);
                jreq.strMethod = "getgroups";
            } //(filterOn Groups)
        } else { 
            if (filterOn) {
                params.push_back("users");
                jreq.params = RPCConvertValues("mybdapaccounts", params);
                jreq.strMethod = "mybdapaccounts";
            } else {
                jreq.params = RPCConvertValues("getusers", params);
                jreq.strMethod = "getusers";
            } //(filterOn Users)
        }

        UniValue result = UniValue(UniValue::VOBJ);
        if (jreq.strMethod != "")
        {
            //Handle RPC errors
            try {
                result = tableRPC.execute(jreq);
            } catch (const UniValue& objError) {
                std::string message = find_value(objError, "message").get_str();
                outputmessage = message;
                QMessageBox::critical(0, "BDAP Error", QObject::tr(outputmessage.c_str()));
                return;
            } catch (const std::exception& e) {
                outputmessage = e.what();
                QMessageBox::critical(0, "BDAP Error", QObject::tr(outputmessage.c_str()));
                return;
            }
        }
        inputtable->clearContents();
        inputtable->setRowCount(0);
        inputtable->setSortingEnabled(true);

        //Parse results and populate QWidgetTable
        for (size_t i {0} ; i < result.size() ; ++i) {
            getName = "";
            getPath = "";
            getExpirationDate = "";


            for (size_t j {0} ; j < result[i].size() ; ++j) {
                keyName = "";
                keyName = result[i].getKeys()[j];

                // "common_name", "object_full_path"
                if (keyName == "common_name") getName = result[i].getValues()[j].get_str();
                if (keyName == "object_full_path") getPath = result[i].getValues()[j].get_str();
                if (keyName == "expires_on") getExpirationDate = FormatISO8601Date(result[i].getValues()[j].get_int64());
            }

            //add row if all criteria have been met
            if ( ((searchCommon == "") && (searchPath == "")) || (((boost::algorithm::to_lower_copy(getName)).find(boost::algorithm::to_lower_copy(searchCommon)) != std::string::npos) && ((boost::algorithm::to_lower_copy(getPath)).find(boost::algorithm::to_lower_copy(searchPath)) != std::string::npos)) ) {
                nNewRow = inputtable->rowCount();
                inputtable->insertRow(nNewRow);
                QTableWidgetItem* commonNameItem = new QTableWidgetItem(QString::fromStdString(getName));
                QTableWidgetItem* fullPathItem = new QTableWidgetItem(QString::fromStdString(getPath));
                QTableWidgetItem* expirationDateItem = new QTableWidgetItem(QString::fromStdString(getExpirationDate));
                inputtable->setItem(nNewRow, 0, commonNameItem);
                inputtable->setItem(nNewRow, 1, fullPathItem);
                inputtable->setItem(nNewRow, 2, expirationDateItem);
                recordsFound++;

            } //if searchcommon


        }; //for loop

        //if we saved the previous state, apply to current results
        if (hasValues) {
            inputtable->horizontalHeader()->setSortIndicator(sortColumn, sortOrder);
        }

        std::string statusString = "Records found: " + std::to_string(recordsFound);

        statusDisplay->setText(std::to_string(recordsFound).c_str());

    } //refreshAccounts

    int size() const
    {
        return cachedAccountStats.size();
    }

    CAccountStats* index(int idx)
    {
        if (idx >= 0 && idx < cachedAccountStats.size())
            return &cachedAccountStats[idx];

        return 0;
    }

}; //BdapAccountTablePriv

BdapAccountTableModel::BdapAccountTableModel(BdapPage* parent) : QAbstractTableModel(parent),
                                                      bdapPage(parent),
                                                      timer(0)
{
    currentIndex = bdapPage->getCurrentIndex();
    userTable = bdapPage->getUserTable();
    groupTable = bdapPage->getGroupTable();
    userStatus = bdapPage->getNumRecordsFound();
    groupStatus = bdapPage->getNumRecordsFound();
    userTable->setColumnWidth(0, COMMONNAME_COLWIDTH); //Common Name (fixed)
    userTable->setColumnWidth(1, FULLPATH_COLWIDTH); //Object Full Path (fixed)
    userTable->setColumnWidth(2, 175);
    groupTable->setColumnWidth(0, COMMONNAME_COLWIDTH); //Common Name (fixed)
    groupTable->setColumnWidth(1, FULLPATH_COLWIDTH); //Object Full Path (fixed)
    groupTable->setColumnWidth(2, 175);
    priv.reset(new BdapAccountTablePriv());
    // default to unsorted
    priv->sortColumn = -1;

    //initialize tables the first time
    refreshUsers();
    refreshGroups();

    //comment out timer, but keep for possible future use
    /*
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(refresh()));
    timer->setInterval(60000); //MODEL_UPDATE_DELAY originally
    startAutoRefresh();
    */
}

BdapAccountTableModel::~BdapAccountTableModel()
{
    // Intentionally left empty
}

void BdapAccountTableModel::startAutoRefresh()
{
    timer->start();
}

void BdapAccountTableModel::stopAutoRefresh()
{
    timer->stop();
}

int BdapAccountTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return priv->size();
}

int BdapAccountTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return columns.length();
}

QVariant BdapAccountTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return QVariant();
}

QVariant BdapAccountTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole && section < columns.size()) {
            return columns[section];
        }
    }
    return QVariant();
}

Qt::ItemFlags BdapAccountTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags retval = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return retval;
}

QModelIndex BdapAccountTableModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    CAccountStats* data = priv->index(row);

    if (data)
        return createIndex(row, column, data);
    return QModelIndex();
}

void BdapAccountTableModel::refresh()
{
    refreshUsers();
    refreshGroups();
}

bool BdapAccountTableModel::walletLocked()
{
    bool walletLocked = true;
    if (bdapPage && bdapPage->getWalletModel() && bdapPage->getWalletModel()->getEncryptionStatus()) {
        WalletModel::EncryptionStatus encStatus = bdapPage->getWalletModel()->getEncryptionStatus();
        if (encStatus == WalletModel::EncryptionStatus::Unencrypted || encStatus == WalletModel::EncryptionStatus::Unlocked)
        {
            walletLocked = false;
        }
    }
    return walletLocked;
}

void BdapAccountTableModel::refreshUsers()
{
    myUsersChecked = bdapPage->getMyUserCheckBoxChecked();
    searchUserCommon = bdapPage->getCommonUserSearch();
    searchUserPath = bdapPage->getPathUserSearch();
    bool walletLocked = BdapAccountTableModel::walletLocked();
    Q_EMIT layoutAboutToBeChanged();
    priv->refreshAccounts(userTable, userStatus, myUsersChecked, searchUserCommon, searchUserPath, walletLocked);
    Q_EMIT layoutChanged();
}

void BdapAccountTableModel::refreshGroups()
{
    myGroupsChecked = bdapPage->getMyGroupCheckBoxChecked();
    searchGroupCommon = bdapPage->getCommonGroupSearch();
    searchGroupPath = bdapPage->getPathGroupSearch();
    bool walletLocked = BdapAccountTableModel::walletLocked();
    Q_EMIT layoutAboutToBeChanged();
    priv->refreshAccounts(groupTable, groupStatus, myGroupsChecked, searchGroupCommon, searchGroupPath, walletLocked);
    Q_EMIT layoutChanged();
}

void BdapAccountTableModel::sort(int column, Qt::SortOrder order)
{
    priv->sortColumn = column;
    priv->sortOrder = order;
    refresh();
}