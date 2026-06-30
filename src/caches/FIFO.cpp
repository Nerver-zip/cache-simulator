#include "FIFO.h"

FIFO::FIFO(const CacheConfig& config)
    : matrix(),
      total_capacity(config.nsets * config.assoc),
      used_capacity(0)
{
    policy = "FIFO";

    for (int i = 0; i < config.nsets; i++) {
        matrix.emplace_back(config.assoc);
    }
}

bool FIFO::execute(uint32_t index, uint32_t tag){
    auto& set = matrix[index];

    if(set.tag_set.find(tag) != set.tag_set.end()){
        ++hits;
        return true;
    }

    misses.total++;

    if((int)set.tag_set.size() == set.capacity){
        uint32_t old = set.q.front();
        set.q.pop();
        set.tag_set.erase(old);

        if(used_capacity == total_capacity){
            ++misses.capacity;
        } else {
            ++misses.conflict;
        }
    }
    else{
        ++used_capacity;
        ++misses.compulsory;
    }

    set.q.push(tag);
    set.tag_set.insert(tag);

    return false;
}