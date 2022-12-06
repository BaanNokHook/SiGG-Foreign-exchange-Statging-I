/**
 * @file currexcdata_object_model.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "currexcdata_object_model.hpp"

CurrExcDataObjectModel::CurrExcDataObjectModel(QObject *parent) : QAbstractListModel(parent)
{

}


void CurrExcDataObjectModel::addCurrExcDataObject(const CurrExcDataObject &object)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    objects_ << object;
    endInsertRows();
}

int CurrExcDataObjectModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return objects_.count();
}

QVariant CurrExcDataObjectModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= objects_.count())
        return QVariant();

    const CurrExcDataObject &object = objects_[index.row()];

    if (role == CurrencyRole)
        return object.currency();
    else if (role == ChangeRole)
        return object.change();
    else if (role == CostRole)
        return object.cost();

    return QVariant();
}


QHash<int, QByteArray> CurrExcDataObjectModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CurrencyRole] = "currency";
    roles[ChangeRole] = "change";
    roles[CostRole] = "cost";

    return roles;
}
