#pragma once

#include "ICache.h"
#include <unordered_set>
#include <queue>

class FIFO : public ICache {
public:
    FIFO(const CacheConfig& config);

    bool execute(int index, int tag) override;
private:
    struct CacheSet {
        const int capacity;
        std::queue<int> q;
        std::unordered_set<int> set; 
    };
};
