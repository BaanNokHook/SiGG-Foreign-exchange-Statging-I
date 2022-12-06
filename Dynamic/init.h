/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_INIT_H
#define DYNAMIC_INIT_H

#include <string>

class CScheduler;
class CWallet;

namespace boost
{
class thread_group;
} // namespace boost

void StartShutdown();
void StartRestart();
void StartMnemonicRestart();
bool ShutdownRequested();
bool MnemonicRestartRequested();
/** Interrupt threads */
void Interrupt(boost::thread_group& threadGroup);
void Shutdown();
//!Initialize the logging infrastructure
void InitLogging();
//!Parameter interaction: change current parameters depending on various rules
void InitParameterInteraction();

/** Initialize bitcoin core: Basic context setup.
 *  @note This can be done before daemonization.
 *  @pre Parameters should be parsed and config file should be read.
 */
bool AppInitBasicSetup();
/**
 * Initialization: parameter interaction.
 * @note This can be done before daemonization.
 * @pre Parameters should be parsed and config file should be read, AppInitBasicSetup should have been called.
 */
bool AppInitParameterInteraction();
/**
 * Initialization sanity checks: ecc init, sanity checks, dir lock.
 * @note This can be done before daemonization.
 * @pre Parameters should be parsed and config file should be read, AppInitParameterInteraction should have been called.
 */
bool AppInitSanityChecks();
/**
 * Bitcoin core main initialization.
 * @note This should only be done after daemonization.
 * @pre Parameters should be parsed and config file should be read, AppInitSanityChecks should have been called.
 */
bool AppInitMain(boost::thread_group& threadGroup, CScheduler& scheduler);
void PrepareShutdown();
void SwapMnemonicWalletFile();

/** The help message mode determines what help message to show */
enum HelpMessageMode {
    HMM_DYNAMICD,
    HMM_DYNAMIC_QT
};

/** Help for options shared between UI and daemon (for -help) */
std::string HelpMessage(HelpMessageMode mode);
/** Returns licensing information (for -version) */
std::string LicenseInfo();

#endif // DYNAMIC_INIT_H
