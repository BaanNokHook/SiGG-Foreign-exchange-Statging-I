/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "walletmodeltransaction.h"

#include "wallet/wallet.h"

WalletModelTransaction::WalletModelTransaction(const QList<SendCoinsRecipient>& _recipients) : recipients(_recipients),
                                                                                               walletTransaction(0),
                                                                                               keyChange(0),
                                                                                               fee(0)
{
    walletTransaction = new CWalletTx();
}

WalletModelTransaction::~WalletModelTransaction()
{
    delete keyChange;
    delete walletTransaction;
}

QList<SendCoinsRecipient> WalletModelTransaction::getRecipients()
{
    return recipients;
}

CWalletTx* WalletModelTransaction::getTransaction()
{
    return walletTransaction;
}

unsigned int WalletModelTransaction::getTransactionSize()
{
    return (!walletTransaction ? 0 : (::GetSerializeSize(walletTransaction->tx, SER_NETWORK, PROTOCOL_VERSION)));
}

CAmount WalletModelTransaction::getTransactionFee()
{
    return fee;
}

void WalletModelTransaction::setTransactionFee(const CAmount& newFee)
{
    fee = newFee;
}

void WalletModelTransaction::reassignAmounts(int nChangePosRet)
{
    int i = 0;
    for (QList<SendCoinsRecipient>::iterator it = recipients.begin(); it != recipients.end(); ++it) {
        SendCoinsRecipient& rcp = (*it);
        {
            if (i == nChangePosRet)
                i++;
            rcp.amount = walletTransaction->tx->vout[i].nValue;
            i++;
        }
    }
}

CAmount WalletModelTransaction::getTotalTransactionAmount()
{
    CAmount totalTransactionAmount = 0;
    Q_FOREACH (const SendCoinsRecipient& rcp, recipients) {
        totalTransactionAmount += rcp.amount;
    }
    return totalTransactionAmount;
}

void WalletModelTransaction::newPossibleKeyChange(CWallet* wallet)
{
    keyChange = new CReserveKey(wallet);
}

CReserveKey* WalletModelTransaction::getPossibleKeyChange()
{
    return keyChange;
}
