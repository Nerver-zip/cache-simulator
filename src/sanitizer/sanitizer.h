#pragma once

#include <string>

struct Parameters {
    int nsets;
    int bsize;
    int assoc;
    std::string policy;
    int outputFlag;
    std::string inputFile;
};

/**
 * @class Sanitizer
 * @brief Classe validadora da entrada, valida constraints e formatação
 * @throws Runtime error caso o input seja inválido
 */
class Sanitizer {
public:
    static Parameters sanitize(int argc, const char* const argv[]);
};
