#include "../caches/LRU.h"
#include "../caches/FIFO.h"
#include "../caches/Random.h"
#include "../caches/LFU.h"
#include <memory>

/*
 * Padrão Factory: Escondemos a lógica de criação das classes concretas LRU, FIFO, LFU e Random
 * e retornamos tudo através da interface comum ICache
 * */

std::unique_ptr<ICache>
createCache(const std::string& policy, const CacheConfig& config, const std::vector<Instruction>& instructions){
    if(policy == "LRU") {
        return std::make_unique<LRU>(
            instructions, config
        );
    }

    if(policy == "FIFO") {
        return std::make_unique<FIFO>(
            instructions, config
        );
    }

    if(policy == "Random") {
        return std::make_unique<Random>(
            instructions, config
        );
    }
    
    
    if(policy == "LFU") {
        return std::make_unique<LFU>(
            instructions, config
        );
    }

    throw std::runtime_error("Unknown policy");
}
