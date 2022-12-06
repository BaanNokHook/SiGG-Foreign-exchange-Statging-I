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
#ifndef PURCHASETABLEMODEL_HPP
#define PURCHASETABLEMODEL_HPP

#include <qqml.h>
#include <QAbstractTableModel>

#include "purchase_object.hpp"

class PurchaseTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

    enum PurchaseRoles
    {
        DateRole = Qt::UserRole + 1,
        PtypeRole,
        AmountRole,
        PriceRole,
        SumRole,
        BankNameRole,
        AccountRole
    };

public:
    explicit PurchaseTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addPurchase(const PurchaseObject &obj);

private:
    QList<PurchaseObject> purchases_;
};

#endif // PURCHASETABLEMODEL_HPP
