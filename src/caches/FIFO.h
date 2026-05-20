#pragma once

#include "../ICache.h"
#include <unordered_set>
#include <queue>

class FIFO : public ICache {
public:
    FIFO(const std::vector<Instruction>& instructions, const CacheConfig& config);

    void run() override;
    
    long long getTotal() const override;

    long long getHits() const override;

    long long getMisses() const override;

private:
    struct CacheSet {
        const int capacity;
        std::queue<int> q;
        std::unordered_set<int> set; 
    };
};
