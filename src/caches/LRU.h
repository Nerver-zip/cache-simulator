#pragma once

#include "ICache.h"
#include "CacheFA.h"
#include <list>
#include <unordered_map>
#include <vector>

class LRU : public ICache {
public:
    LRU(const CacheConfig& config);

    bool execute(int index, int tag) override;
private:
    struct CacheSet {
        const int capacity;
        std::list<int> linkedList;
        std::unordered_map<int, std::list<int>::iterator> map;
        CacheSet(int capacity) : capacity(capacity) {}
    };
    
    std::vector<CacheSet> set;
    CacheFA cacheFA;
};
