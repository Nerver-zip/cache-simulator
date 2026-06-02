#include <cstdint>
#include <iomanip>
#include <ios>
#include <iostream>
#include "decode/decoder.h"
#include "factory/factory.h"
#include "sanitizer/sanitizer.h"
#include "reader/FileReader.h"

int main(int argc, char* argv[]){
    
    Parameters params;

    try {
        params = Sanitizer::sanitize(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
        return 1;
    }
        
    CacheConfig config(params.nsets, params.bsize, params.assoc);
    FileReader reader(params.inputFile);
    auto cache = createCache(params.policy, config); 

    uint32_t address;
    while(reader.nextInt32(address)){
        auto [index, tag] = Decoder::decodeAddress(address, config);  
        cache->execute(index, tag);
    }
    
    if(params.outputFlag){
        std::cout << cache->getTotal() << " ";
        std::cout << std::fixed << std::setprecision(4) << cache->getHitRate() << " ";
        std::cout << std::fixed << std::setprecision(4) <<cache->getMissRate() << " ";
        std::cout << std::fixed << std::setprecision(4) << cache->getCompulsoryMissRate() << " ";
        std::cout << std::fixed << std::setprecision(4) << cache->getCapacityMissRate()<< " ";
        std::cout << std::fixed << std::setprecision(4) << cache->getConflictMissRate() << "\n";
    }
    else {
        // Formato livre
    }
    
    return 0;
}
