#pragma once

#include "ICache.h"
#include <list>
#include <unordered_map>
#include <vector>

/**
 * @class LFUCache
 * @brief LFU Cache - Least Frequently Used. Quando faltar capacidade
 * ela ejetará o elemento de menor frequência. Em caso de empate, a política de fallback é o LRU.
 */
class LFU : public ICache {
public:
    LFU(const CacheConfig& config);

    void execute(int index, int tag) override;
private:
    struct CacheSet {
        const int capacity;
        std::list<int> linkedList;
        std::unordered_map<int, std::list<int>::iterator> map;
        
        CacheSet(int capacity) : capacity(capacity) {}
    };
};
