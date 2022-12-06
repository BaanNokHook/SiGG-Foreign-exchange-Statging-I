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
#include "validation.h"
#include "utiltime.h"

// Sanity test: this should loop ten times, and
// min/max/average should be close to 100ms.
static void Sleep100ms(benchmark::State& state)
{
    while (state.KeepRunning()) {
        MilliSleep(100);
    }
}

BENCHMARK(Sleep100ms);

// Extremely fast-running benchmark:
#include <math.h>

volatile double sum = 0.0; // volatile, global so not optimized away

static void Trig(benchmark::State& state)
{
    double d = 0.01;
    while (state.KeepRunning()) {
        sum += sin(d);
        d += 0.000001;
    }
}

BENCHMARK(Trig);
