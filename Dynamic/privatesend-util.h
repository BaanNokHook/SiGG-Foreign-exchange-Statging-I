/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PRIVATESENDUTIL_H
#define PRIVATESENDUTIL_H

#include "wallet/wallet.h"

class CKeyHolder
{
private:
    CReserveKey reserveKey;
    CPubKey pubKey;

public:
    CKeyHolder(CWallet* pwalletIn);
    CKeyHolder(CKeyHolder&&) = default;
    CKeyHolder& operator=(CKeyHolder&&) = default;
    void KeepKey();
    void ReturnKey();

    CScript GetScriptForDestination() const;
};

class CKeyHolderStorage
{
private:
    std::vector<std::unique_ptr<CKeyHolder> > storage;
    mutable CCriticalSection cs_storage;

public:
    CScript AddKey(CWallet* pwalletIn);
    void KeepAll();
    void ReturnAll();
};
#endif //PRIVATESENDUTIL_H