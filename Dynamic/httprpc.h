/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_HTTPRPC_H
#define DYNAMIC_HTTPRPC_H

#include <map>
#include <string>

class HTTPRequest;

/** Start HTTP RPC subsystem.
 * Precondition; HTTP and RPC has been started.
 */
bool StartHTTPRPC();
/** Interrupt HTTP RPC subsystem.
 */
void InterruptHTTPRPC();
/** Stop HTTP RPC subsystem.
 * Precondition; HTTP and RPC has been stopped.
 */
void StopHTTPRPC();

/** Start HTTP REST subsystem.
 * Precondition; HTTP and RPC has been started.
 */
bool StartREST();
/** Interrupt RPC REST subsystem.
 */
void InterruptREST();
/** Stop HTTP REST subsystem.
 * Precondition; HTTP and RPC has been stopped.
 */
void StopREST();

#endif // DYNAMIC_HTTPRPC_H
