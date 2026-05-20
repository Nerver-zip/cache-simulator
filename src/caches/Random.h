#pragma once

#include "../ICache.h"
#include <vector>

class Random : public ICache {
public:
    Random(const std::vector<Instruction>& instructions, const CacheConfig& config);

    void run() override;
    
    long long getTotal() const override;

    long long getHits() const override;

    long long getMisses() const override;

private:
    struct CacheSet {
        const int capacity;
        std::vector<int> bucket;
        
        CacheSet(int capacity) : capacity(capacity), bucket(capacity) {}
    };
};
