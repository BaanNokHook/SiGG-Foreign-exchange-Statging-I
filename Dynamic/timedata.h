/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_TIMEDATA_H
#define DYNAMIC_TIMEDATA_H

#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <vector>

static const int64_t DEFAULT_MAX_TIME_ADJUSTMENT = 70 * 60;

class CNetAddr;

/** 
 * Median filter over a stream of values.
 * Returns the median of the last N numbers
 */
template <typename T>
class CMedianFilter
{
private:
    std::vector<T> vValues;
    std::vector<T> vSorted;
    unsigned int nSize;

public:
    CMedianFilter(unsigned int size, T initial_value) : nSize(size)
    {
        vValues.reserve(size);
        vValues.push_back(initial_value);
        vSorted = vValues;
    }

    void input(T value)
    {
        if (vValues.size() == nSize) {
            vValues.erase(vValues.begin());
        }
        vValues.push_back(value);

        vSorted.resize(vValues.size());
        std::copy(vValues.begin(), vValues.end(), vSorted.begin());
        std::sort(vSorted.begin(), vSorted.end());
    }

    T median() const
    {
        int size = vSorted.size();
        assert(size > 0);
        if (size & 1) // Odd number of elements
        {
            return vSorted[size / 2];
        } else // Even number of elements
        {
            return (vSorted[size / 2 - 1] + vSorted[size / 2]) / 2;
        }
    }

    int size() const
    {
        return vValues.size();
    }

    std::vector<T> sorted() const
    {
        return vSorted;
    }
};

/** Functions to keep track of adjusted P2P time */
int64_t GetTimeOffset();
int64_t GetAdjustedTime();
int64_t GetNodesOffset();
void AddTimeData(const CNetAddr& ip, int64_t nTime);

#endif // DYNAMIC_TIMEDATA_H
