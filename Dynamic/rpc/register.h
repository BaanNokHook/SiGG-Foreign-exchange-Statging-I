/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_RPCREGISTER_H
#define DYNAMIC_RPCREGISTER_H

/** These are in one header file to avoid creating tons of single-function
 * headers for everything under src/rpc/ */
class CRPCTable;

/** Register block chain RPC commands */
void RegisterBlockchainRPCCommands(CRPCTable& tableRPC);
/** Register P2P networking RPC commands */
void RegisterNetRPCCommands(CRPCTable& tableRPC);
/** Register miscellaneous RPC commands */
void RegisterMiscRPCCommands(CRPCTable& tableRPC);
/** Register mining RPC commands */
void RegisterMiningRPCCommands(CRPCTable& tableRPC);
/** Register raw transaction RPC commands */
void RegisterRawTransactionRPCCommands(CRPCTable& tableRPC);
/** Register dynode RPC commands */
void RegisterDynodeRPCCommands(CRPCTable& tableRPC);
/** Register governance RPC commands */
void RegisterGovernanceRPCCommands(CRPCTable& tableRPC);
/** Register fluid RPC commands */
void RegisterFluidRPCCommands(CRPCTable& tableRPC);
/** Register BDAP Domain Entry RPC commands */
void RegisterDomainEntryRPCCommands(CRPCTable &tableRPC);
/** Register DHT RPC commands */
void RegisterDHTRPCCommands(CRPCTable &tableRPC);
/** Register BDAP Linking RPC commands */
void RegisterLinkingRPCCommands(CRPCTable &tableRPC);
/** Register Raw BDAP Account RPC commands */
void RegisterRawBDAPAccountRPCCommands(CRPCTable &tableRPC);
/** Register Raw BDAP Audit RPC commands */
void RegisterAuditRPCCommands(CRPCTable &tableRPC);
/** Register Raw BDAP Certificate RPC commands */
void RegisterCertificateRPCCommands(CRPCTable &tableRPC);

static inline void RegisterAllCoreRPCCommands(CRPCTable& t)
{
    RegisterBlockchainRPCCommands(t);
    RegisterNetRPCCommands(t);
    RegisterMiscRPCCommands(t);
    RegisterMiningRPCCommands(t);
    RegisterRawTransactionRPCCommands(t);
    RegisterDynodeRPCCommands(t);
    RegisterGovernanceRPCCommands(t);
    RegisterFluidRPCCommands(t);
    RegisterDomainEntryRPCCommands(t);
    RegisterDHTRPCCommands(t);
    RegisterLinkingRPCCommands(t);
    RegisterRawBDAPAccountRPCCommands(t);
    RegisterAuditRPCCommands(t);
    RegisterCertificateRPCCommands(t);
}

#endif // DYNAMIC_RPCREGISTER_H