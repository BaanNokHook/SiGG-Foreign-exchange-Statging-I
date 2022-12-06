/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "checkpoints.h"

#include "chain.h"
#include "chainparams.h"
#include "uint256.h"
#include "validation.h"

#include <stdint.h>

#include <boost/foreach.hpp>

namespace Checkpoints
{
CBlockIndex* GetLastCheckpoint(const CCheckpointData& data)
{
    const MapCheckpoints& checkpoints = data.mapCheckpoints;

    BOOST_REVERSE_FOREACH (const MapCheckpoints::value_type& i, checkpoints) {
        const uint256& hash = i.second;
        BlockMap::const_iterator t = mapBlockIndex.find(hash);
        if (t != mapBlockIndex.end())
            return t->second;
    }
    return NULL;
}

bool fEnabled = true;

bool CheckBlock(int nHeight, const uint256& hash, bool fMatchesCheckpoint)
{
    if (!fEnabled)
        return true;

    const MapCheckpoints& checkpoints = Params().Checkpoints().mapCheckpoints;
    MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
    // If looking for an exact match, then return false
    if (i == checkpoints.end()) return !fMatchesCheckpoint;
    return hash == i->second;
}
} // namespace Checkpoints