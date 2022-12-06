/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_ASKPASSPHRASEDIALOG_H
#define DYNAMIC_QT_ASKPASSPHRASEDIALOG_H

#include <QDialog>

class WalletModel;

namespace Ui
{
class AskPassphraseDialog;
}

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class AskPassphraseDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode {
        Encrypt,      /**< Ask passphrase twice and encrypt */
        UnlockMixing, /**< Ask passphrase and unlock only for mixing */
        Unlock,       /**< Ask passphrase and unlock */
        ChangePass,   /**< Ask old passphrase + new passphrase twice */
        Decrypt       /**< Ask passphrase and decrypt wallet */
    };

    explicit AskPassphraseDialog(Mode mode, QWidget* parent);
    ~AskPassphraseDialog();

    void accept();

    void setModel(WalletModel* model);

private:
    Ui::AskPassphraseDialog* ui;
    Mode mode;
    WalletModel* model;
    bool fCapsLock;

private Q_SLOTS:
    void textChanged();
    void secureClearPassFields();

protected:
    bool event(QEvent* event);
    bool eventFilter(QObject* object, QEvent* event);
};

#endif // DYNAMIC_QT_ASKPASSPHRASEDIALOG_H
