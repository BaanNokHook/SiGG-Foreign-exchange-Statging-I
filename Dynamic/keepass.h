/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_KEEPASS_H
#define DYNAMIC_KEEPASS_H

#include "support/allocators/secure.h"

#include <univalue.h>

class CKeePassIntegrator;

static const unsigned int DEFAULT_KEEPASS_HTTP_PORT = 19455;

extern CKeePassIntegrator keePassInt;

class CKeePassIntegrator
{
private:
    static const int KEEPASS_CRYPTO_KEY_SIZE = 32;
    static const int KEEPASS_CRYPTO_BLOCK_SIZE = 16;
    static const int KEEPASS_HTTP_CONNECT_TIMEOUT = 30;
    static const char* KEEPASS_HTTP_HOST;

    bool bIsActive;
    unsigned int nPort;
    SecureString sKeyBase64;
    SecureString sKey;
    SecureString sUrl;
    //SecureString sSubmitUrl;
    std::string strKeePassId;
    std::string strKeePassEntryName;

    class CKeePassRequest
    {
        UniValue requestObj;
        std::string strType;
        std::string strIV;
        SecureString sKey;

        void init();

    public:
        void addStrParameter(std::string strName, std::string strValue); // Regular
        void addStrParameter(std::string strName, SecureString sValue);  // Encrypt
        std::string getJson();

        CKeePassRequest(SecureString sKey, std::string strType)
        {
            this->sKey = sKey;
            this->strType = strType;
            init();
        };
    };


    class CKeePassEntry
    {
        SecureString sUuid;
        SecureString sName;
        SecureString sLogin;
        SecureString sPassword;

    public:
        CKeePassEntry(SecureString sUuid, SecureString sName, SecureString sLogin, SecureString sPassword) : sUuid(sUuid), sName(sName), sLogin(sLogin), sPassword(sPassword)
        {
        }

        SecureString getUuid()
        {
            return sUuid;
        }

        SecureString getName()
        {
            return sName;
        }

        SecureString getLogin()
        {
            return sLogin;
        }

        SecureString getPassword()
        {
            return sPassword;
        }
    };


    class CKeePassResponse
    {
        bool bSuccess;
        std::string strType;
        std::string strIV;
        SecureString sKey;

        void parseResponse(std::string strResponse);

    public:
        UniValue responseObj;
        CKeePassResponse(SecureString sKey, std::string strResponse)
        {
            this->sKey = sKey;
            parseResponse(strResponse);
        }

        bool getSuccess()
        {
            return bSuccess;
        }

        SecureString getSecureStr(std::string strName);
        std::string getStr(std::string strName);
        std::vector<CKeePassEntry> getEntries();

        SecureString decrypt(std::string strValue); // DecodeBase64 and decrypt arbitrary string value
    };

    static SecureString generateRandomKey(size_t nSize);
    static std::string constructHTTPPost(const std::string& strMsg, const std::map<std::string, std::string>& mapRequestHeaders);
    void doHTTPPost(const std::string& strRequest, int& nStatus, std::string& strResponse);
    void rpcTestAssociation(bool bTriggerUnlock);
    std::vector<CKeePassEntry> rpcGetLogins();
    void rpcSetLogin(const SecureString& sWalletPass, const SecureString& sEntryId);

public:
    CKeePassIntegrator();
    void init();
    static SecureString generateKeePassKey();
    void rpcAssociate(std::string& strId, SecureString& sKeyBase64);
    SecureString retrievePassphrase();
    void updatePassphrase(const SecureString& sWalletPassphrase);
};

#endif // DYNAMIC_KEEPASS_H