#pragma once

#include <cstdint>
#include <iostream>
#include <string>

/**
 * @class Decoder
 * @brief Decodifica uma linha vinda do arquivo .bin e entrega o índice e a tag para a simulação da cache
 */
class Decoder {
public:
    static std::pair<int,int> decodeAddress(uint32_t address){
        int index, tag;
    
        // Lógica de decodificação

        return {index, tag};
    };
};
