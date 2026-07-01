#pragma once

#include "../caches/LRU.h"
#include "../caches/FIFO.h"
#include "../caches/Random.h"
#include <memory>

/*
 * Padrão Factory: Escondemos a lógica de criação das classes concretas LRU, FIFO e Random
 * e retornamos tudo através da interface comum ICache
 * */
std::unique_ptr<ICache>
createCache(const std::string& policy, const CacheConfig& config);
