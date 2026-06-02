#include "decoder.h"
#include <cmath>

std::pair<uint32_t, uint32_t> Decoder::decodeAddress(uint32_t address, const CacheConfig& config){
    const auto [nsets, bsize, assoc] = config;
    
    // Formato do endereço:
    //[ [tag][índice][offset] ]

    int bits_offset = log2(bsize);
    int bits_index = log2(nsets);

    uint32_t tag = address >> (bits_index + bits_offset);
    uint32_t index = (address >> bits_offset) & ((1 << bits_index) - 1);

    return {index, tag};
}
