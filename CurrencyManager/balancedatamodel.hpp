/**
 * @file balancedatamodel.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BALANCEDATAMODEL_HPP
#define BALANCEDATAMODEL_HPP

#include <qqml.h>
#include <QAbstractTableModel>

#include "balancedataobject.hpp"

class BalanceDataModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

    enum BalanceRoles
    {
        DateRole = Qt::UserRole + 1,
        BalanceRole
    };

public:
    explicit BalanceDataModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addBalanceHistoryObject(const BalanceDataObject& data);

private:
    QList<BalanceDataObject> data_;
};

#endif // BALANCEDATAMODEL_HPP
