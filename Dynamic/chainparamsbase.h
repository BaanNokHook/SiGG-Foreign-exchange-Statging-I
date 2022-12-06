/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_CHAINPARAMSBASE_H
#define DYNAMIC_CHAINPARAMSBASE_H

#include <string>
#include <vector>

static const int DEFAULT_P2P_PORT = 33300;

/**
 * CBaseChainParams defines the base parameters (shared between dynamic-cli and dynamicd)
 * of a given instance of the Dynamic system.
 */
class CBaseChainParams
{
public:
    /** BIP70 chain name strings (main, test or regtest) */
    static const std::string MAIN;
    static const std::string TESTNET;
    static const std::string REGTEST;
    static const std::string PRIVATENET;

    const std::string& DataDir() const { return strDataDir; }
    int RPCPort() const { return nRPCPort; }

protected:
    CBaseChainParams() {}

    int nRPCPort;
    std::string strDataDir;
};

/**
 * Append the help messages for the chainparams options to the
 * parameter string.
 */
void AppendParamsHelpMessages(std::string& strUsage, bool debugHelp = true);

/**
 * Return the currently selected parameters. This won't change after app
 * startup, except for unit tests.
 */
const CBaseChainParams& BaseParams();

CBaseChainParams& BaseParams(const std::string& chain);

/** Sets the params returned by Params() to those for the given network. */
void SelectBaseParams(const std::string& chain);

/**
 * Looks for -regtest, -testnet and returns the appropriate BIP70 chain name.
 * @return CBaseChainParams::MAX_NETWORK_TYPES if an invalid combination is given. CBaseChainParams::MAIN by default.
 */
std::string ChainNameFromCommandLine();

/**
 * Return true if SelectBaseParamsFromCommandLine() has been called to select
 * a network.
 */
bool AreBaseParamsConfigured();

#endif // DYNAMIC_CHAINPARAMSBASE_H
