/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "bench.h"

#include "support/lockedpool.h"

#include <iostream>
#include <vector>

#define ASIZE 2048
#define BITER 5000
#define MSIZE 2048

static void LockedPool(benchmark::State& state)
{
    void *synth_base = reinterpret_cast<void*>(0x08000000);
    const size_t synth_size = 1024*1024;
    Arena b(synth_base, synth_size, 16);

    std::vector<void*> addr;
    for (int x=0; x<ASIZE; ++x)
        addr.push_back(0);
    uint32_t s = 0x12345678;
    while (state.KeepRunning()) {
        for (int x=0; x<BITER; ++x) {
            int idx = s & (addr.size()-1);
            if (s & 0x80000000) {
                b.free(addr[idx]);
                addr[idx] = 0;
            } else if(!addr[idx]) {
                addr[idx] = b.alloc((s >> 16) & (MSIZE-1));
            }
            bool lsb = s & 1;
            s >>= 1;
            if (lsb)
                s ^= 0xf00f00f0; // LFSR period 0xf7ffffe0
        }
    }
    for (void *ptr: addr)
        b.free(ptr);
    addr.clear();
}

BENCHMARK(LockedPool);
