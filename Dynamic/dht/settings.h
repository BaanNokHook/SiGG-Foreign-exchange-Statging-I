/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DYNAMIC_DHT_SETTINGS_H
#define DYNAMIC_DHT_SETTINGS_H

#include <libtorrent/session.hpp>

static constexpr int MIN_DHT_PROTO_VERSION = 71000;

class CDHTSettings {
private:
    libtorrent::session* ses;
    libtorrent::session_params params;
    std::string listen_interfaces;
    std::string dht_bootstrap_nodes;
    std::string user_agent;
    std::string peer_fingerprint;
    uint16_t nPort;
    uint16_t nTotalThreads;
    bool fMultiThreads;

public:
    CDHTSettings(const uint16_t ordinal, const uint16_t threads, const bool multithreaded);

    void LoadSettings();
    void LoadPeerID(const std::string& strPeerID);

    libtorrent::settings_pack GetSettingsPack() const { return params.settings; }
    libtorrent::dht_settings GetDHTSettings() const { return params.dht_settings; }
    libtorrent::session_params GetSessionParams() const { return params; }
    libtorrent::session* GetSession() const { return ses; }

private:
    void LoadPeerList();

};

#endif // DYNAMIC_DHT_SETTINGS_H