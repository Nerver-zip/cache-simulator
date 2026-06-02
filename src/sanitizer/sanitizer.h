#pragma once

#include <string>

struct Parameters {
    int nsets;
    int bsize;
    int assoc;
    std::string policy;
    bool outputFlag;
    std::string inputFile;
    
    Parameters() = default;

    Parameters(int nsets, int bsize, int assoc, std::string policy, bool outputFlag, std::string inputFile) : 
    nsets(nsets), bsize(bsize), assoc(assoc), policy(policy), outputFlag(outputFlag), inputFile(inputFile) {}
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
