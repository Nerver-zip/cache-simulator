#pragma once

#include "ICache.h"
#include <list>
#include <unordered_map>
#include <vector>

class LRU : public ICache {
public:
    LRU(const CacheConfig& config);
    
    void execute(int index, int tag) override;
private:
    struct CacheSet {
        const int capacity;
        std::list<int> linkedList;
        std::unordered_map<int, std::list<int>::iterator> map;
        
        CacheSet(int capacity) : capacity(capacity) {}
    };
};
