#include "factory.h"

std::unique_ptr<ICache>
createCache(const std::string& policy, const CacheConfig& config){
    if(policy == "L")
        return std::make_unique<LRU>(config);

    if(policy == "F")
        return std::make_unique<FIFO>(config);

    if(policy == "R")
        return std::make_unique<Random>(config);
    
    if(policy == "LFU")
        return std::make_unique<LFU>(config);

    throw std::runtime_error("Unknown policy");
}
