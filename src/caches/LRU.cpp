#include "LRU.h"

LRU::LRU(const CacheConfig& config) : cacheFA(config) {
    set.resize(config.nsets, CacheSet(config.assoc));
}

bool LRU::execute(int index, int tag){
    auto& [capacity, linkedList, map] = set[index];
    auto it = map.find(tag);
        
    bool capacity_miss = cacheFA.isMissFullyAssociative(tag);

    // tag não existe
    if(it == map.end()){
        ++misses.total; 

        if((int)linkedList.size() == capacity){
            map.erase(linkedList.back());
            linkedList.pop_back();
            
            if(capacity_miss)
                ++misses.capacity;
            else
                ++misses.conflict;
        }
        else
            ++misses.compulsory;

        linkedList.push_front(tag);
        map.insert({tag, linkedList.begin()});
        return false;
    }

    // tag existe
    auto list_it = it->second;
    linkedList.splice(linkedList.begin(), linkedList, list_it);
    ++hits;
    return true;
}
