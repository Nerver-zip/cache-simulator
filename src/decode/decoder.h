#pragma once

#include <fstream>
#include <iostream>
#include <string>

/**
 * @class Decoder
 * @brief Decodifica uma linha vinda do arquivo .bin e entrega o índice e a tag para a simulação da cache
 */
class Decoder {
public:
    static std::pair<int,int> getInstruction(const std::string& line){
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
        file.open(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file");
        }
    }

    bool nextLine(std::string& line) {
        return static_cast<bool>(std::getline(file, line));
    }

    bool eof() const {
        return file.eof();
    }
};
