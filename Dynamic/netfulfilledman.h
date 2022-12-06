/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_NETFULFILLEDMAN_H
#define DYNAMIC_NETFULFILLEDMAN_H

#include "netaddress.h"
#include "serialize.h"
#include "sync.h"

class CNetFulfilledRequestManager;
extern CNetFulfilledRequestManager netfulfilledman;

// Fulfilled requests are used to prevent nodes from asking for the same data on sync
// and from being banned for doing so too often.
class CNetFulfilledRequestManager
{
private:
    typedef std::map<std::string, int64_t> fulfilledreqmapentry_t;
    typedef std::map<CService, fulfilledreqmapentry_t> fulfilledreqmap_t;

    //keep track of what node has/was asked for and when
    fulfilledreqmap_t mapFulfilledRequests;
    CCriticalSection cs_mapFulfilledRequests;

    void RemoveFulfilledRequest(const CService& addr, const std::string& strRequest);

public:
    CNetFulfilledRequestManager() {}

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        LOCK(cs_mapFulfilledRequests);
        READWRITE(mapFulfilledRequests);
    }

    void AddFulfilledRequest(const CService& addr, const std::string& strRequest);
    bool HasFulfilledRequest(const CService& addr, const std::string& strRequest);

    void CheckAndRemove();
    void Clear();

    std::string ToString() const;

    void DoMaintenance();
};

#endif // DYNAMIC_NETFULFILLEDMAN_H
