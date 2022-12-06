/**
 * @file balancedatamodel.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "balancedatamodel.hpp"

BalanceDataModel::BalanceDataModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int BalanceDataModel::rowCount(const QModelIndex &) const
{
    return data_.size();
}

int BalanceDataModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant BalanceDataModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= data_.count())
        return QVariant();

    const BalanceDataObject &obj = data_[index.row()];

    if (role == DateRole)
        return obj.date();
    else if (role == BalanceRole)
        return obj.balance();

    return QVariant();
}

QHash<int, QByteArray> BalanceDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DateRole] = "date";
    roles[BalanceRole] = "balance";

    return roles;
}

void BalanceDataModel::addBalanceHistoryObject(const BalanceDataObject &obj)
{
    beginInsertRows(QModelIndex(), rowCount(), columnCount());
    data_ << obj;
    endInsertRows();
}
