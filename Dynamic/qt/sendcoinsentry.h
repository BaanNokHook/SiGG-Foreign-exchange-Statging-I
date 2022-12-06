/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_SENDCOINSENTRY_H
#define DYNAMIC_QT_SENDCOINSENTRY_H

#include "walletmodel.h"

#include <QStackedWidget>

class PlatformStyle;
class WalletModel;

namespace Ui
{
class SendCoinsEntry;
}

/**
 * A single entry in the dialog for sending Dynamic.
 * Stacked widget, with different UIs for payment requests
 * with a strong payee identity.
 */
class SendCoinsEntry : public QStackedWidget
{
    Q_OBJECT

public:
    explicit SendCoinsEntry(const PlatformStyle* platformStyle, QWidget* parent = 0);
    ~SendCoinsEntry();

    void setModel(WalletModel* model);
    bool validate();
    SendCoinsRecipient getValue();

    /** Return whether the entry is still empty and unedited */
    bool isClear();

    void setValue(const SendCoinsRecipient& value);
    void setAddress(const QString& address);

    /** Set up the tab chain manually, as Qt messes up the tab chain by default in some cases
     *  (issue https://bugreports.qt-project.org/browse/QTBUG-10907).
     */
    QWidget* setupTabChain(QWidget* prev);

    void setFocus();

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void removeEntry(SendCoinsEntry* entry);
    void payAmountChanged();
    void subtractFeeFromAmountChanged();

private Q_SLOTS:
    void deleteClicked();
    void on_payTo_textChanged(const QString& address);
    void on_addressBookButton_clicked();
    void on_pasteButton_clicked();
    void updateDisplayUnit();

private:
    SendCoinsRecipient recipient;
    Ui::SendCoinsEntry* ui;
    WalletModel* model;
    const PlatformStyle* platformStyle;

    bool updateLabel(const QString& address);
};

#endif // DYNAMIC_QT_SENDCOINSENTRY_H
