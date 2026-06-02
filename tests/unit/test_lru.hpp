#pragma once

#include "test_framework.h"
#include "../../src/factory/factory.h"

inline void test_lru(){
    #define MISS false
    #define HIT true

    // Tamanho do bloco não importa aqui
    // Definimos uma cache de 2 conjuntos de 4 vias cada
    {
        CacheConfig config(2, 4, 8);
        auto cache = createCache("LRU", config);

        // Teste de hit/miss
        // Dados: 2,4,6,8,2,10,4
        // Deve dar um hit no 2
        // Expulsar o 4 quando colocar 10
        // E assim dando miss no 4, o que valida o LRU
        // já que expulsamos o correto
        
        ASSERT_EQUAL(MISS, cache->execute(0, 2));
        ASSERT_EQUAL(MISS, cache->execute(0, 4));
        ASSERT_EQUAL(MISS, cache->execute(0, 6));
        ASSERT_EQUAL(MISS, cache->execute(0, 8));
        ASSERT_EQUAL(HIT,  cache->execute(0, 2));
        ASSERT_EQUAL(MISS, cache->execute(0, 10));
        ASSERT_EQUAL(MISS, cache->execute(0, 4));

        std::cout << "----------------------------------" << "\n"; 
    }
    
    // Simulando lista = [1,3,5,7,1,1,9,2,4,6,8,10,12,21]
    {
        CacheConfig config(2, 4, 8);
        auto cache = createCache("LRU", config);
        
        ASSERT_EQUAL(MISS, cache->execute(1, 1)); // falta
        ASSERT_EQUAL(MISS, cache->execute(1, 3)); // falta
        ASSERT_EQUAL(MISS, cache->execute(1, 5)); // falta
        ASSERT_EQUAL(MISS, cache->execute(1, 7)); // falta
        ASSERT_EQUAL(HIT,  cache->execute(1, 1)); // hit
        ASSERT_EQUAL(HIT, cache->execute(1, 1)); // hit
        ASSERT_EQUAL(HIT, cache->execute(1, 1));  // hit
        ASSERT_EQUAL(MISS, cache->execute(1, 9)); // conflito
        ASSERT_EQUAL(MISS, cache->execute(0, 2)); // falta
        ASSERT_EQUAL(MISS, cache->execute(0, 4)); // falta
        ASSERT_EQUAL(MISS, cache->execute(0, 6)); // falta
        ASSERT_EQUAL(MISS, cache->execute(0, 8));  // falta
        ASSERT_EQUAL(MISS, cache->execute(0, 10)); // miss cap
        ASSERT_EQUAL(MISS, cache->execute(0, 12)); // miss cap
        ASSERT_EQUAL(MISS, cache->execute(1, 21)); // miss cal
        

        ASSERT_EQUAL_VERBOSE(12.0/15, cache->getMissRate(), 12.0/15, cache->getMissRate());
        ASSERT_EQUAL_VERBOSE(3.0/15, cache->getHitRate(), 12.0/15, cache->getHitRate());
        ASSERT_EQUAL_VERBOSE(8.0/12, cache->getCompulsoryMissRate(), 8.0/12, cache->getCompulsoryMissRate());
        ASSERT_EQUAL_VERBOSE(1.0/12, cache->getConflictMissRate(), 1.0/12, cache->getConflictMissRate());
        ASSERT_EQUAL_VERBOSE(3.0/12, cache->getCapacityMissRate(), 3.0/12, cache->getCapacityMissRate());
    
        std::cout << "----------------------------------" << "\n"; 
    }
    
    
    // Testando o LRU
    // Lista = [0,2,4,8,8,0,2,10] -> Deve sair o 4 quando 10 chegar
    {
        CacheConfig config(1, 4, 8);
        auto cache = createCache("LRU", config);
        
        cache->execute(0, 0);
        cache->execute(0, 2);
        cache->execute(0, 4);
        cache->execute(0, 8);
        cache->execute(0, 8);
        cache->execute(0, 0);
        cache->execute(0, 2);
        cache->execute(0, 10);
        
        std::cout << "LRU must have replaced 4" << "\n";
        ASSERT_EQUAL(MISS, cache->execute(0, 4));


        std::cout << "----------------------------------" << "\n"; 
    }

    // Testando o LRU
    // Lista = [0,2,4,8,8,0,8,4,2,10] -> Deve sair o 0 quando 10 chegar
    {
        CacheConfig config(1, 4, 8);
        auto cache = createCache("LRU", config);
        
        cache->execute(0, 0);
        cache->execute(0, 2);
        cache->execute(0, 4);
        cache->execute(0, 8);
        cache->execute(0, 8);
        cache->execute(0, 0);
        cache->execute(0, 8);
        cache->execute(0, 4);
        cache->execute(0, 2);
        cache->execute(0, 10);
        
        std::cout << "LRU must have replaced 0" << "\n";
        ASSERT_EQUAL(MISS, cache->execute(0, 0));

        std::cout << "----------------------------------" << "\n"; 
    }
    
    // Testando o LRU
    // Lista = [0,2,4,8,8,0,8,2,4,8,0,10] -> Deve sair o 2 quando 10 chegar
    {
        CacheConfig config(1, 4, 8);
        auto cache = createCache("LRU", config);
        
        cache->execute(0, 0);
        cache->execute(0, 2);
        cache->execute(0, 4);
        cache->execute(0, 8);
        cache->execute(0, 8);
        cache->execute(0, 0);
        cache->execute(0, 8);
        cache->execute(0, 2);
        cache->execute(0, 4);
        cache->execute(0, 8);
        cache->execute(0, 0);
        cache->execute(0, 10);
        
        std::cout << "LRU must have replaced 2" << "\n";
        ASSERT_EQUAL(MISS, cache->execute(0, 2));

        std::cout << "----------------------------------" << "\n"; 
    }
}
