#include <iostream>
#include "decode/decoder.h"
#include "factory/factory.h"
#include "sanitizer/sanitizer.h"

int main(int argc, char* argv[]){

    auto params = Sanitizer::sanitize(argc, argv);
    
    CacheConfig config(params.nsets, params.bsize, params.assoc);
    FileReader reader(params.inputFile);
    auto cache = createCache(params.policy, config); 

    std::string line;

    while(reader.nextLine(line)){
        auto [index, tag] = Decoder::getInstruction(line);        
        cache->execute(index, tag);
    }

    std::cout << cache->getTotal();
    std::cout << cache->getHitRate();
    std::cout << cache->getMissRate();
    std::cout << cache->getMisses().compulsory / cache->getMisses().total;
    std::cout << cache->getMisses().capacity / cache->getMisses().total;
    std::cout << cache->getMisses().conflict / cache->getMisses().total;
    
    return 0;
}
