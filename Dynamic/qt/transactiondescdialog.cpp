/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "transactiondescdialog.h"
#include "ui_transactiondescdialog.h"

#include "guiutil.h"
#include "transactiontablemodel.h"

#include <QModelIndex>
#include <QSettings>
#include <QString>

TransactionDescDialog::TransactionDescDialog(const QModelIndex& idx, QWidget* parent) : QDialog(parent),
                                                                                        ui(new Ui::TransactionDescDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Details for %1").arg(idx.data(TransactionTableModel::TxIDRole).toString()));

    /* Open CSS when configured */
    this->setStyleSheet(GUIUtil::loadStyleSheet());

    QString desc = idx.data(TransactionTableModel::LongDescriptionRole).toString();
    ui->detailText->setHtml(desc);
}

TransactionDescDialog::~TransactionDescDialog()
{
    delete ui;
}
