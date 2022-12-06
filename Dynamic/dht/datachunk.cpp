/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "dht/datachunk.h"

#include "bdap/utils.h"
#include "hash.h"
#include "streams.h"
#include "uint256.h"


void CDataChunk::Serialize(std::vector<unsigned char>& vchData) 
{
    CDataStream dsDataChunk(SER_NETWORK, PROTOCOL_VERSION);
    dsDataChunk << *this;
    vchData = std::vector<unsigned char>(dsDataChunk.begin(), dsDataChunk.end());
}

bool CDataChunk::UnserializeFromData(const std::vector<unsigned char>& vchData) 
{
    try {
        CDataStream dsDataChunk(vchData, SER_NETWORK, PROTOCOL_VERSION);
        dsDataChunk >> *this;
    } catch (std::exception& e) {
        SetNull();
        return false;
    }
    return true;
}