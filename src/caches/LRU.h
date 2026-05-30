#pragma once

#include "ICache.h"
#include <list>
#include <unordered_map>
#include <vector>

class LRU : public ICache {
public:
    LRU(const CacheConfig& config);

    bool execute(int index, int tag) override;
private:
    const int set_capacity;
    const int total_capacity;
    int used_capacity;

    struct CacheSet {
        std::list<int> linkedList;
        std::unordered_map<int, std::list<int>::iterator> map;
    };
    
    std::vector<CacheSet> set;
};
