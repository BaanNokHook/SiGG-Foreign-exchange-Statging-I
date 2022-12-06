/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_PRIVATESENDCONFIG_H
#define DYNAMIC_QT_PRIVATESENDCONFIG_H

#include <QDialog>

namespace Ui
{
class PrivateSendConfig;
}
class WalletModel;

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class PrivateSendConfig : public QDialog
{
    Q_OBJECT

public:
    PrivateSendConfig(QWidget* parent = 0);
    ~PrivateSendConfig();

    void setModel(WalletModel* model);


private:
    Ui::PrivateSendConfig* ui;
    WalletModel* model;
    void configure(bool enabled, int coins, int rounds);

private Q_SLOTS:

    void clickBasic();
    void clickHigh();
    void clickMax();
};

#endif // DYNAMIC_QT_PRIVATESENDCONFIG_H
