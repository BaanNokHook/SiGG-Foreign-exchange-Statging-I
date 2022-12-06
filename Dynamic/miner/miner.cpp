/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "miner/miner.h"
#include "chainparams.h"
#include "consensus/consensus.h"
#include "consensus/validation.h"
#include "miner/internal/miners-controller.h"
#include "net.h"
#include "primitives/transaction.h"
#include "utilmoneystr.h"
#include "validation.h"
#include "validationinterface.h"

void InitMiners(const CChainParams& chainparams, CConnman& connman)
{
    if (!gMiners)
        gMiners.reset(new MinersController(chainparams, connman));
}

void StartMiners()
{
    assert(gMiners);
    gMiners->Start();
};

void ShutdownMiners()
{
    if (gMiners)
        gMiners->Shutdown();
};

void ShutdownCPUMiners()
{
    if (gMiners)
        gMiners->group_cpu().Shutdown();
};

void ShutdownGPUMiners()
{
#ifdef ENABLE_GPU
    if (gMiners)
        gMiners->group_gpu().Shutdown();
#endif // ENABLE_GPU
};

int64_t GetHashRate()
{
    if (gMiners)
        return gMiners->GetHashRate();
    return 0;
};

int64_t GetCPUHashRate()
{
    if (gMiners)
        return gMiners->group_cpu().GetHashRate();
    return 0;
};

int64_t GetGPUHashRate()
{
#ifdef ENABLE_GPU
    if (gMiners)
        return gMiners->group_gpu().GetHashRate();
#endif // ENABLE_GPU
    return 0;
};

void SetCPUMinerThreads(uint8_t target)
{
    assert(gMiners);
    gMiners->group_cpu().SetSize(target);
};

void SetGPUMinerThreads(uint8_t target)
{
#ifdef ENABLE_GPU
    assert(gMiners);
    gMiners->group_gpu().SetSize(target);
#endif // ENABLE_GPU
};

std::unique_ptr<MinersController> gMiners = {nullptr};
