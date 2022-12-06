/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_CHECKPOINTS_H
#define DYNAMIC_CHECKPOINTS_H

#include "uint256.h"

#include <map>

class CBlockIndex;
struct CCheckpointData;

/**
 * Block-chain checkpoints are compiled-in sanity checks.
 * They are updated every release or three.
 */
namespace Checkpoints
{
//! Returns last CBlockIndex* in mapBlockIndex that is a checkpoint
CBlockIndex* GetLastCheckpoint(const CCheckpointData& data);

//! Returns true if block passes checkpoint checks
bool CheckBlock(int nHeight, const uint256& hash, bool fMatchesCheckpoint = false);

} //namespace Checkpoints

#endif // DYNAMIC_CHECKPOINTS_H
