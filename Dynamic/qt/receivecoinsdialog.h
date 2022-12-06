/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_RECEIVECOINSDIALOG_H
#define DYNAMIC_QT_RECEIVECOINSDIALOG_H

#include "guiutil.h"

#include <QDialog>
#include <QHeaderView>
#include <QItemSelection>
#include <QKeyEvent>
#include <QMenu>
#include <QPoint>
#include <QVariant>

class OptionsModel;
class PlatformStyle;
class WalletModel;

namespace Ui
{
class ReceiveCoinsDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog for requesting payment of Dynamics */
class ReceiveCoinsDialog : public QDialog
{
    Q_OBJECT

public:
    enum ColumnWidths {
        DATE_COLUMN_WIDTH = 130,
        ADDRESS_COLUMN_WIDTH = 160,
        LABEL_COLUMN_WIDTH = 120,
        AMOUNT_MINIMUM_COLUMN_WIDTH = 180,
        MINIMUM_COLUMN_WIDTH = 120
    };

    explicit ReceiveCoinsDialog(const PlatformStyle* platformStyle, QWidget* parent = 0);
    ~ReceiveCoinsDialog();

    void setModel(WalletModel* model);

public Q_SLOTS:
    void clear();
    void reject() override;
    void accept() override;

protected:
    virtual void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::ReceiveCoinsDialog* ui;
    GUIUtil::TableViewLastColumnResizingFixer* columnResizingFixer;
    WalletModel* model;
    QMenu* contextMenu;
    const PlatformStyle* platformStyle;

    QModelIndex selectedRow();
    void copyColumnToClipboard(int column);
    virtual void resizeEvent(QResizeEvent* event) override;

private Q_SLOTS:
    void on_receiveButton_clicked();
    void on_showRequestButton_clicked();
    void on_removeRequestButton_clicked();
    void on_recentRequestsView_doubleClicked(const QModelIndex& index);
    void recentRequestsView_selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void updateDisplayUnit();
    void showMenu(const QPoint& point);
    void copyAddress();
    void copyLabel();
    void copyMessage();
    void copyAmount();
    void copyURI();
};

#endif // DYNAMIC_QT_RECEIVECOINSDIALOG_H
