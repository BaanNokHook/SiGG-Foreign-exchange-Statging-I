/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MESSAGESIGNER_H
#define MESSAGESIGNER_H

#include "key.h"

/** Helper class for signing messages and checking their signatures
 */
class CMessageSigner
{
public:
    /// Set the private/public key values, returns true if successful
    static bool GetKeysFromSecret(const std::string& strSecret, CKey& keyRet, CPubKey& pubkeyRet);
    /// Sign the message, returns true if successful
    static bool SignMessage(const std::string& strMessage, std::vector<unsigned char>& vchSigRet, const CKey& key);
    /// Verify the message signature, returns true if succcessful
    static bool VerifyMessage(const CPubKey& pubkey, const std::vector<unsigned char>& vchSig, const std::string& strMessage, std::string& strErrorRet);
    /// Verify the message signature, returns true if succcessful
    static bool VerifyMessage(const CKeyID& keyID, const std::vector<unsigned char>& vchSig, const std::string& strMessage, std::string& strErrorRet);
};

/** Helper class for signing hashes and checking their signatures
 */
class CHashSigner
{
public:
    /// Sign the hash, returns true if successful
    static bool SignHash(const uint256& hash, const CKey& key, std::vector<unsigned char>& vchSigRet);
    /// Verify the hash signature, returns true if succcessful
    static bool VerifyHash(const uint256& hash, const CPubKey& pubkey, const std::vector<unsigned char>& vchSig, std::string& strErrorRet);
    /// Verify the hash signature, returns true if succcessful
    static bool VerifyHash(const uint256& hash, const CKeyID& keyID, const std::vector<unsigned char>& vchSig, std::string& strErrorRet);
};

#endif