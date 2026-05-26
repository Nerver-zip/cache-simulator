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
    const int capacity;

    struct CacheSet {
        std::list<int> linkedList;
        std::unordered_map<int, std::list<int>::iterator> map;
    };
    
    std::vector<CacheSet> set;
    CacheFA cacheFA;
};
