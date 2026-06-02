#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include "../caches/ICache.h"

/**
 * @class Decoder
 * @brief Decodifica uma linha vinda do arquivo .bin e entrega o índice e a tag para a simulação da cache
 */
class Decoder {
public:
    static std::pair<uint32_t, uint32_t> decodeAddress(uint32_t address, const CacheConfig& config);
};
