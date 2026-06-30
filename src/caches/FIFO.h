#pragma once

#include "ICache.h"
#include <cstdint>
#include <unordered_set>
#include <queue>
#include <vector>

class FIFO : public ICache {
public:
    FIFO(const CacheConfig& config);

    bool execute(uint32_t index, uint32_t tag) override;

private:
    struct CacheSet {
        int capacity;
        std::queue<uint32_t> q;
        std::unordered_set<uint32_t> tag_set;

        CacheSet(int cap) : capacity(cap) {}
    };

    std::vector<CacheSet> matrix;

    int total_capacity;
    int used_capacity;
};