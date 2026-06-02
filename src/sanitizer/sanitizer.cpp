#include "sanitizer.h"
#include <cstring>
#include <stdexcept>
#include <string>
#include <string_view>
#include <charconv>
#include <vector>

Parameters Sanitizer::sanitize(int argc, const char* const argv[]){
    const int MAX_SIZE = 1 << 30;
    constexpr std::size_t MAX_ARG_LENGTH = 100;
    
    // Helper que checa overflow, número válido e potência de 2
    auto parsePositiveInt = [](std::string_view s, int arg) {
        int value;

        auto [ptr, ec] = std::from_chars(
            s.data(),
            s.data() + s.size(),
            value
        );
        
        if (ec == std::errc::invalid_argument) {
            throw std::runtime_error("Argument " + std::to_string(arg) + " invalid argument");
        }

        if (ec == std::errc::result_out_of_range) {
            throw std::runtime_error("Argument " + std::to_string(arg) + " overflowed");
        }

        if (ptr != s.data() + s.size()) {
            throw std::runtime_error("Argument " + std::to_string(arg) + " has trailing characters");
        }

        if(value <= 0 || __builtin_popcount(value) != 1){
            throw std::runtime_error("Argument " + std::to_string(value) + " must be a positive power of two");
        }

        return value;
    };

    // ./cache_simulator -h imprime ajuda
    auto throwHelp = []() {
        throw std::runtime_error(
            "Usage:\n"
            "./cache_simulator <nsets> <bsize> <assoc> <policy> <flag> <file>\n"
            "Example:\n"
            "./cache_simulator 32 32 4 L 1 bin_1000.bin"
        );
    };

    if(argc == 2 && std::string_view(argv[1]) == "-h"){
        throwHelp();
    }

    if(argc != 7){
        throw std::runtime_error("Invalid number of arguments. Run ./cache_simulator -h for help.");
    }
    
    // 
    for(int i = 1; i < 7; ++i){
        std::string_view s = argv[i];
        if(s.size() > MAX_ARG_LENGTH)
            throw std::runtime_error("Invalid argument. Run ./cache_simulator -h for help");
    }
    
    // Primeiros 3 argumentos
    // Tudo que não for número ou potência de 2 deve ser rejeitado
    long long size = 1;
    std::vector<int> size_params; 
    for(int i = 1; i < 4; ++i){
        int n = parsePositiveInt(argv[i], i);
        
        if (size > std::numeric_limits<long long>::max() / n) {
            throw std::overflow_error("Cache size caused integer overflow. Choose a smaller cache size");
        }
        size *= n;
        size_params.push_back(n);
    }
    
    if(size > MAX_SIZE){
        throw std::overflow_error("Cache size overflowed max capacity. Choose a smaller cache size");
    }
    
    // Validação da política
    if(std::string_view(argv[4]) != "L" && std::string_view(argv[4]) != "R" && std::string_view(argv[4]) != "F" && std::string_view(argv[4]) != "LFU")
        throw std::runtime_error("Unknown policy. Check ./cache_simulator -h for help");
    
    // Validação da flag
    if(std::string_view(argv[5]) != "0" && std::string_view(argv[5]) != "1")
        throw std::runtime_error("<flag> must be either 0 or 1");
    
    if(!std::string_view(argv[6]).ends_with(".bin")){
        throw std::runtime_error("<file> must be a .bin file");
    }

    return Parameters(size_params[0], size_params[1], size_params[2], argv[4], std::string_view(argv[5]).contains("1"), argv[6]);
}
