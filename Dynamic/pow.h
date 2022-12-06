/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_POW_H
#define DYNAMIC_POW_H

#include <arith_uint256.h>
#include <chain.h>
#include <consensus/params.h>
#include <stdint.h>
#include <sync.h>
#include <util.h>

class arith_uint256;
class CBlockHeader;
class CBlockIndex;
class uint256;

const CBlockIndex* GetLastBlockIndex(const CBlockIndex* pindex);

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader& block,  const Consensus::Params&);
unsigned int DigiShield(const CBlockIndex* pindexLast, 
	const int64_t AveragingWindow, const int64_t AveragingWindowTimespan, 
	const int64_t MinActualTimespan, const int64_t MaxActualTimespan, 
	const Consensus::Params& params);

/** Check whether a block hash satisfies the proof-of-work requirement specified by nBits */
bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params&);

#endif // DYNAMIC_POW_H
