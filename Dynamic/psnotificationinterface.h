/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_PSNOTIFICATIONINTERFACE_H
#define DYNAMIC_PSNOTIFICATIONINTERFACE_H

#include "validationinterface.h"

class CPSNotificationInterface : public CValidationInterface
{
public:
    CPSNotificationInterface(CConnman& connmanIn) : connman(connmanIn) {}
    virtual ~CPSNotificationInterface() = default;

    // a small helper to initialize current block height in sub-modules on startup
    void InitializeCurrentBlockTip();

protected:
    // CValidationInterface
    void AcceptedBlockHeader(const CBlockIndex* pindexNew) override;
    void NotifyHeaderTip(const CBlockIndex* pindexNew, bool fInitialDownload) override;
    void UpdatedBlockTip(const CBlockIndex* pindexNew, const CBlockIndex* pindexFork, bool fInitialDownload) override;
    void SyncTransaction(const CTransaction& tx, const CBlockIndex* pindex, int posInBlock) override;

private:
    CConnman& connman;
};

#endif // DYNAMIC_PSNOTIFICATIONINTERFACE_H
