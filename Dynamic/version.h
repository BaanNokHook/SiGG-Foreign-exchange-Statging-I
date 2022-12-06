/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_VERSION_H
#define DYNAMIC_VERSION_H

/**
 * network protocol versioning
 */
static const int PROTOCOL_VERSION = 72500;

//! initial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

//! In this version, 'getheaders' was introduced.
static const int GETHEADERS_VERSION = 60800;

//! disconnect from peers older than this proto version
static const int MIN_PEER_PROTO_VERSION = 71100;

//! nTime field added to CAddress, starting with this version;
//! if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 31402;

//! BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

//! "mempool" command, enhanced "getdata" behavior starts with this version
static const int MEMPOOL_GD_VERSION = 60002;

//! "filter*" commands are disabled without NODE_BLOOM after and including this version
static const int NO_BLOOM_VERSION = 60800;

//! "sendheaders" command and announcing blocks with headers starts with this version
static const int SENDHEADERS_VERSION = 60800;

//! short-id-based block download starts with this version
static const int SHORT_IDS_BLOCKS_VERSION = 71000;

#endif // DYNAMIC_VERSION_H
