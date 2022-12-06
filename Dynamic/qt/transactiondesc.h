/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_TRANSACTIONDESC_H
#define DYNAMIC_QT_TRANSACTIONDESC_H

#include <QObject>
#include <QString>

class TransactionRecord;

class CWallet;
class CWalletTx;

/** Provide a human-readable extended HTML description of a transaction.
 */
class TransactionDesc : public QObject
{
    Q_OBJECT

public:
    static QString toHTML(CWallet* wallet, CWalletTx& wtx, TransactionRecord* rec, int unit);

private:
    TransactionDesc() {}

    static QString FormatTxStatus(const CWalletTx& wtx);
};

#endif // DYNAMIC_QT_TRANSACTIONDESC_H
