/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DYNAMIC_CONSENSUS_CONSENSUS_H
#define DYNAMIC_CONSENSUS_CONSENSUS_H

/** The maximum allowed size for a transaction, in bytes */
static const unsigned int MAX_TX_SIZE = 1000000; // 1 MB to match the default maximum network send size.
/** The maximum allowed size for a serialized block, in bytes (network rule) */
static const unsigned int MAX_BLOCK_SIZE = 4194304; //4MB
/** The maximum allowed number of signature check operations in a block (network rule) */
static const unsigned int MAX_BLOCK_SIGOPS = MAX_BLOCK_SIZE / 50;
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = 10;

/** Flags for nSequence and nLockTime locks */
enum {
    /* Interpret sequence numbers as relative lock-time constraints. */
    LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

    /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
    LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};

#endif // DYNAMIC_CONSENSUS_CONSENSUS_H
