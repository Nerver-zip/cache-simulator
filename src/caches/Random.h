#pragma once

#include "ICache.h"
#include <vector>
#include <random>

class Random : public ICache {
public:
    Random(const CacheConfig& config);

    bool execute(uint32_t index, uint32_t tag) override;

private:
    std::mt19937 gen;
    std::vector <std::vector<uint32_t >> matrix;
    const int capacity;
    const int total_capacity;
    int used_capacity;
    std::uniform_int_distribution<int> dist;
};
