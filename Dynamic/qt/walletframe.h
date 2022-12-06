/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_WALLETFRAME_H
#define DYNAMIC_QT_WALLETFRAME_H

#include <QFrame>
#include <QMap>

class ClientModel;
class DynamicGUI;
class PlatformStyle;
class SendCoinsRecipient;
class WalletModel;
class WalletView;

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE

class WalletFrame : public QFrame
{
    Q_OBJECT

public:
    explicit WalletFrame(const PlatformStyle* platformStyle, DynamicGUI* _gui = 0);
    ~WalletFrame();

    void setClientModel(ClientModel* clientModel);

    bool addWallet(const QString& name, WalletModel* walletModel);
    bool setCurrentWallet(const QString& name);
    bool removeWallet(const QString& name);
    void removeAllWallets();

    bool handlePaymentRequest(const SendCoinsRecipient& recipient);

    void showOutOfSyncWarning(bool fShow);

Q_SIGNALS:
    /** Notify that the user has requested more information about the out-of-sync warning */
    void requestedSyncWarningInfo();

private:
    QStackedWidget* walletStack;
    DynamicGUI* gui;
    ClientModel* clientModel;
    QMap<QString, WalletView*> mapWalletViews;

    bool bOutOfSync;

    const PlatformStyle* platformStyle;

    WalletView* currentWalletView();

public Q_SLOTS:
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
    /** Switch to Dynode page */
    void gotoDynodePage();
    /** Switch to mining page */
    void gotoMiningPage();
    /** Switch to bdap page */
    void gotoBdapPage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");

    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");
    /** Encrypt the wallet */
    void encryptWallet(bool status);
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
    void unlockWallet();
    /** Lock wallet */
    void lockWallet();

    /** Show used sending addresses */
    void usedSendingAddresses();
    /** Show used receiving addresses */
    void usedReceivingAddresses();

    /** Pass on signal over requested out-of-sync-warning information */
    void outOfSyncWarningClicked();
};

#endif // DYNAMIC_QT_WALLETFRAME_H
