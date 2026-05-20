#pragma once

#include "../ICache.h"
#include <list>
#include <unordered_map>
#include <vector>

class LRU : public ICache {
public:
    LRU(const std::vector<Instruction>& instructions, const CacheConfig& config);
    
    void run() override;
    
    long long getTotal() const override;

    long long getHits() const override;

    long long getMisses() const override;

private:
    struct CacheSet {
        const int capacity;
        std::list<int> linkedList;
        std::unordered_map<int, std::list<int>::iterator> map;
        
        CacheSet(int capacity) : capacity(capacity) {}
    };
};
