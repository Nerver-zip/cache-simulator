#pragma once

#include "ICache.h"
#include <cstdint>
#include <vector>

class Random : public ICache {
public:
    Random(const CacheConfig& config);

    bool execute(uint32_t index, uint32_t tag) override;
    
private:
    struct CacheSet {
        const int capacity;
        std::vector<int> bucket;
        
        CacheSet(int capacity) : capacity(capacity), bucket(capacity) {}
    };
};
