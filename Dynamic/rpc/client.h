/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_RPCCLIENT_H
#define DYNAMIC_RPCCLIENT_H

#include <univalue.h>

UniValue RPCConvertValues(const std::string& strMethod, const std::vector<std::string>& strParams);
/** Non-RFC4627 JSON parser, accepts internal values (such as numbers, true, false, null)
 * as well as objects and arrays.
 */

/** Convert named arguments to command-specific RPC representation */
UniValue RPCConvertNamedValues(const std::string& strMethod, const std::vector<std::string>& strParams);

/** Non-RFC4627 JSON parser, accepts internal values (such as numbers, true, false, null)
 * as well as objects and arrays.
 */
UniValue ParseNonRFCJSONValue(const std::string& strVal);

#endif // DYNAMIC_RPCCLIENT_H
