#pragma once

#include <cstdint>
#include <fstream>
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

struct CacheConfig {
    const int nsets;
    int bsize;
    int assoc;

    CacheConfig(int nsets, int bsize, int assoc) : nsets(nsets), bsize(bsize), assoc(assoc) {}  
};

class FileReader {
private:
    std::ifstream file;

public:
    FileReader(const std::string& filename) {
        file.open(filename, std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file");
        }
    }

    bool nextInt32(uint32_t& value) {
        uint8_t bytes[4];

        if (!file.read(reinterpret_cast<char*>(bytes), 4)) {
            return false;
        }

        value =
            (uint32_t(bytes[0]) << 24) |
            (uint32_t(bytes[1]) << 16) |
            (uint32_t(bytes[2]) << 8)  |
            uint32_t(bytes[3]);

        return true;
    }

    bool eof() const {
        return file.eof();
    }
};
