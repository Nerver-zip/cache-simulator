#include "CacheFA.h"

CacheFA::CacheFA(const CacheConfig& config) : capacity(config.nsets * config.assoc) {}

bool CacheFA::isMissFullyAssociative(int tag){
    auto it = map.find(tag);
    
    bool capacity_miss = false;
    
    if(it == map.end()){
        linkedList.push_front(tag);
        if((int)linkedList.size() > capacity){
            capacity_miss = true;
            map.erase(linkedList.back());
            map.insert({tag, linkedList.begin()});
        }
        return capacity_miss;
    }
    
    auto list_it = it->second;
    linkedList.splice(linkedList.begin(), linkedList, list_it);
    return false;
}
