#pragma once

#include "ICache.h"
#include <cstdint>
#include <unordered_set>
#include <queue>

class FIFO : public ICache {
public:
    FIFO(const CacheConfig& config);

    bool execute(uint32_t index, uint32_t tag) override;
private:
    struct CacheSet {
        const int capacity;
        std::queue<int> q;
        std::unordered_set<int> set; 
    };
};
