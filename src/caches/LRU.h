#pragma once

#include "ICache.h"
#include <cstdint>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>

class LRU : public ICache {
public:
    LRU(const CacheConfig& config);

    bool execute(uint32_t index, uint32_t tag) override;
private:
    const int set_capacity;
    const int total_capacity;
    int used_capacity;

    struct CacheSet {
        std::list<uint32_t> linkedList;
        std::unordered_map<uint32_t, std::list<uint32_t>::iterator> map;
    };
    
    std::vector<CacheSet> set;
};
