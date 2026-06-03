#include "Random.h"

#include "Random.h"

Random::Random(const CacheConfig &config) : 
    gen(std::random_device{}()), matrix(config.nsets), 
    capacity(config.assoc), total_capacity(config.nsets * config.assoc), 
    used_capacity(), dist(0, config.assoc - 1) {}

bool Random::execute(uint32_t index, uint32_t tag){
    auto &row = matrix[index];

    for (int i = 0; i < (int)row.size(); i++)
    {
        if(row[i] == tag){
            ++hits;
            return true;
        }
    }

    misses.total++;

    if((int)row.size() == capacity){
        row[dist(gen)] = tag;
        if(used_capacity == total_capacity){
            ++misses.capacity;
        }
        else{
            ++misses.conflict;
        }
    }
    else{
        row.push_back(tag);
        ++used_capacity;
        ++misses.compulsory;
    }

    return false;
}
