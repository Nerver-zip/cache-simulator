#include "LRU.h"
#include <cstdint>

LRU::LRU(const CacheConfig& config) : set_capacity(config.assoc), total_capacity(config.nsets * config.assoc), used_capacity(0), set(config.nsets) {}

bool LRU::execute(uint32_t index, uint32_t tag){
    auto& [linkedList, map] = set[index];
    auto it = map.find(tag);

    // tag não existe
    if(it == map.end()){
        ++misses.total; 

        if((int)linkedList.size() == set_capacity){
            map.erase(linkedList.back());
            linkedList.pop_back();
            
            if(used_capacity == total_capacity)
                ++misses.capacity;
            else
                ++misses.conflict;
        }
        else{
            ++misses.compulsory;
            ++used_capacity;
        }

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
