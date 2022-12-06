/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_ADDRDB_H
#define DYNAMIC_ADDRDB_H

#include "serialize.h"

#include <boost/filesystem/path.hpp>
#include <map>
#include <string>

class CSubNet;
class CAddrMan;
class CDataStream;

typedef enum BanReason {
    BanReasonUnknown = 0,
    BanReasonNodeMisbehaving = 1,
    BanReasonManuallyAdded = 2
} BanReason;

class CBanEntry
{
public:
    static const int CURRENT_VERSION = 1;
    int nVersion;
    int64_t nCreateTime;
    int64_t nBanUntil;
    uint8_t banReason;

    CBanEntry()
    {
        SetNull();
    }

    CBanEntry(int64_t nCreateTimeIn)
    {
        SetNull();
        nCreateTime = nCreateTimeIn;
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        READWRITE(this->nVersion);
        READWRITE(nCreateTime);
        READWRITE(nBanUntil);
        READWRITE(banReason);
    }

    void SetNull()
    {
        nVersion = CBanEntry::CURRENT_VERSION;
        nCreateTime = 0;
        nBanUntil = 0;
        banReason = BanReasonUnknown;
    }

    std::string banReasonToString()
    {
        switch (banReason) {
        case BanReasonNodeMisbehaving:
            return "node misbehaving";
        case BanReasonManuallyAdded:
            return "manually added";
        default:
            return "unknown";
        }
    }
};

typedef std::map<CSubNet, CBanEntry> banmap_t;

/** Access to the (IP) address database (peers.dat) */
class CAddrDB
{
private:
    boost::filesystem::path pathAddr;

public:
    CAddrDB();
    bool Write(const CAddrMan& addr);
    bool Read(CAddrMan& addr);
    bool Read(CAddrMan& addr, CDataStream& ssPeers);
};

/** Access to the banlist database (banlist.dat) */
class CBanDB
{
private:
    boost::filesystem::path pathBanlist;

public:
    CBanDB();
    bool Write(const banmap_t& banSet);
    bool Read(banmap_t& banSet);
};

#endif // DYNAMIC_ADDRDB_H