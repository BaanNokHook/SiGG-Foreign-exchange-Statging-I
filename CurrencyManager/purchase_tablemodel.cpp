/**
 * @file purchase_tablemodel.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "purchase_tablemodel.hpp"

PurchaseTableModel::PurchaseTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int PurchaseTableModel::rowCount(const QModelIndex&) const
{
    return purchases_.size();
}

int PurchaseTableModel::columnCount(const QModelIndex&) const
{
    return 7;
}

QVariant PurchaseTableModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= purchases_.count())
        return QVariant();

    const PurchaseObject &purchase = purchases_[index.row()];

    if (role == DateRole)
        return purchase.date();
    else if (role == PtypeRole)
        return purchase.ptype();
    else if (role == AmountRole)
        return purchase.amount();
    else if (role == PriceRole)
        return purchase.price();
    else if (role == SumRole)
        return purchase.sum();
    else if (role == BankNameRole)
        return purchase.bank_name();
    else if (role == AccountRole)
        return purchase.account();

    return QVariant();
}

QHash<int, QByteArray> PurchaseTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DateRole] = "date";
    roles[PtypeRole] = "ptype";
    roles[AmountRole] = "amount";
    roles[PriceRole] = "price";
    roles[SumRole] = "sum";
    roles[BankNameRole] = "bank_name";
    roles[AccountRole] = "account";

    return roles;
}

void PurchaseTableModel::addPurchase(const PurchaseObject &obj)
{
    beginInsertRows(QModelIndex(), rowCount(), columnCount());
    purchases_ << obj;
    endInsertRows();
}
