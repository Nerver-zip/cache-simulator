#include <cstdint>
#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include "decode/decoder.h"
#include "factory/factory.h"
#include "sanitizer/sanitizer.h"
#include "reader/FileReader.h"

#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_RESET   "\033[0m"

using namespace std;

int main(int argc, char* argv[]){
    auto start_time = chrono::steady_clock::now();

    Parameters params;
    
    try {
        params = Sanitizer::sanitize(argc, argv);
    } catch (const exception& e) {
        cout << e.what() << "\n";
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
    
    cout << std::fixed;
    cout << std::setprecision(4);
    if(params.outputFlag){
        cout << cache->getTotal() << " ";
        cout << cache->getHitRate() << " ";
        cout << cache->getMissRate() << " ";
        cout << cache->getCompulsoryMissRate() << " ";
        cout << cache->getCapacityMissRate()<< " ";
        cout << cache->getConflictMissRate() << "\n";
    }
    else {
        auto end = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start_time);
        
        cout << COLOR_YELLOW << "\nCache parameters" << "\n"; 
        cout << COLOR_GREEN << "Cache size: " << COLOR_RESET << params.nsets * params.assoc * params.bsize << "KB" << "\n";
        cout << COLOR_GREEN << "Number of sets: " << COLOR_RESET << params.nsets << "\n";
        cout << COLOR_GREEN << "Block size: " << COLOR_RESET << params.bsize << "\n";
        cout << COLOR_GREEN << "Associativity: " << COLOR_RESET << params.assoc << "\n";
        cout << COLOR_GREEN << "Policy: " << COLOR_RESET << cache->getPolicy() << "\n"; 

        cout << "--------------------------" << "\n";

        cout << COLOR_YELLOW << "Simulation Results:" << "\n";
        cout << COLOR_GREEN <<"Instructions executed: " << COLOR_RESET << cache->getTotal() << "\n";
        cout << COLOR_GREEN <<"Elapsed time: " << COLOR_RESET << elapsed << "\n";
        cout << COLOR_GREEN <<"Number of hits: " << COLOR_RESET << cache->getHits() << "\n";
        cout << COLOR_GREEN <<"Number of misses: " << COLOR_RESET << cache->getMisses().total << "\n";
        cout << COLOR_GREEN <<"Number of compulsory misses: " << COLOR_RESET << cache->getMisses().compulsory << "\n";
        cout << COLOR_GREEN <<"Number of conflict misses: " << COLOR_RESET << cache->getMisses().conflict << "\n";
        cout << COLOR_GREEN << "Number of capacity misses: " << COLOR_RESET << cache->getMisses().capacity << "\n";
        cout << COLOR_GREEN << "Number of replacements: " << COLOR_RESET << cache->getMisses().conflict + cache->getMisses().capacity << "\n";
        cout << COLOR_GREEN << "Hit rate: " << COLOR_RESET << cache->getHitRate() << "\n";
        cout << COLOR_GREEN << "Miss rate: " << COLOR_RESET << cache->getMissRate() << "\n";
        cout << COLOR_GREEN << "Compulsory miss rate: " << COLOR_RESET << cache->getCompulsoryMissRate() << "\n";
        cout << COLOR_GREEN << "Capacity miss rate: " << COLOR_RESET << cache->getCapacityMissRate() << "\n";
        cout << COLOR_GREEN << "Conflict miss rate: " << COLOR_RESET << cache->getConflictMissRate() << "\n";
    }
    
    return 0;
}
