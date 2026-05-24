#include "decoder.h"
#include <cmath>


std::pair<int,int> Decoder::decodeAddress(uint32_t address, const CacheConfig& config){
    const auto [nsets, assoc, bsize] = config;
    
    // Formato do endereço:
    //[ [tag][índice][offset] ]

    int bits_offset = log2(bsize);
    int bits_index = log2(nsets);

    int tag = address >> (bits_index + bits_offset);
    int index = (address >> bits_offset) & ((1 << bits_index) - 1);

    return {index, tag};
}
