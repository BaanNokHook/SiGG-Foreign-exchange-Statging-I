/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DYNAMIC_DHT_LIMITS_H
#define DYNAMIC_DHT_LIMITS_H

/**!
These limit classes define allowed salts (records) that the DHT will accept for storage.
The first version contains a list of acceptable salts but in future versions, this list will
be dynamic.  Application developers that want to store data in the DHT can purchase a certificate
that allows their custom op code.
*/

#include <string>
#include <vector>

class CAllowDataCode {
public:
    std::string strSalt;
    uint16_t nMaximumSlots;
    unsigned int nStartHeight;
    uint64_t nExpireTime;

    CAllowDataCode(const std::string& salt, const uint16_t maxslots, const unsigned int& start, const uint64_t expire) :
        strSalt(salt), nMaximumSlots(maxslots), nStartHeight(start), nExpireTime(expire) {}

};

bool CheckSalt(const std::string& strSalt, const unsigned int nHeight, std::string& strErrorMessage);
bool CheckPubKey(const std::vector<unsigned char>& vchPubKey);
uint16_t GetMaximumSlots(const std::string& salt);

#endif // DYNAMIC_DHT_LIMITS_H
