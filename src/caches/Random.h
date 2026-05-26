#pragma once

#include "ICache.h"
#include <vector>

class Random : public ICache {
public:
    Random(const CacheConfig& config);

    bool execute(int index, int tag) override;
    
private:
    struct CacheSet {
        const int capacity;
        std::vector<int> bucket;
        
        CacheSet(int capacity) : capacity(capacity), bucket(capacity) {}
    };
};
