#pragma once

#include "ICache.h"
#include <list>
#include <unordered_map>

class CacheFA {
public:
    CacheFA(const CacheConfig& config);

    bool isMissFullyAssociative(int tag);
private:
    const int capacity;
    std::list<int> linkedList;
    std::unordered_map<int, std::list<int>::iterator> map;
    CacheFA(int capacity) : capacity(capacity) {}
};
