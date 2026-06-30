#pragma once

#include "test_framework.h"
#include "../../src/factory/factory.h"

inline void test_fifo(){
    #define MISS false
    #define HIT true

    {
        // Definimos uma cache de 2 conjuntos de 4 vias cada
        CacheConfig config(2, 8, 4);
        auto cache = createCache("F", config);

        // Dados: 2,4,6,8,2,10,4
        // FIFO: remove o 2 (primeiro que entrou)

        ASSERT_EQUAL(MISS, cache->execute(0, 2));
        ASSERT_EQUAL(MISS, cache->execute(0, 4));
        ASSERT_EQUAL(MISS, cache->execute(0, 6));
        ASSERT_EQUAL(MISS, cache->execute(0, 8));
        ASSERT_EQUAL(HIT,  cache->execute(0, 2));
        ASSERT_EQUAL(MISS, cache->execute(0, 10)); // remove 2
        ASSERT_EQUAL(HIT,  cache->execute(0, 4));  // ainda está!

        std::cout << "----------------------------------" << "\n"; 
    }

    {
        CacheConfig config(2, 8, 4);
        auto cache = createCache("F", config);

        ASSERT_EQUAL(MISS, cache->execute(1, 1));
        ASSERT_EQUAL(MISS, cache->execute(1, 3));
        ASSERT_EQUAL(MISS, cache->execute(1, 5));
        ASSERT_EQUAL(MISS, cache->execute(1, 7));
        ASSERT_EQUAL(HIT,  cache->execute(1, 1));
        ASSERT_EQUAL(HIT,  cache->execute(1, 1));
        ASSERT_EQUAL(HIT,  cache->execute(1, 1));
        ASSERT_EQUAL(MISS, cache->execute(1, 9)); // remove 1 (FIFO)
        
        ASSERT_EQUAL(MISS, cache->execute(0, 2));
        ASSERT_EQUAL(MISS, cache->execute(0, 4));
        ASSERT_EQUAL(MISS, cache->execute(0, 6));
        ASSERT_EQUAL(MISS, cache->execute(0, 8));
        ASSERT_EQUAL(MISS, cache->execute(0, 10));
        ASSERT_EQUAL(MISS, cache->execute(0, 12));
        ASSERT_EQUAL(MISS, cache->execute(1, 21));

        std::cout << "----------------------------------" << "\n"; 
    }


    // Lista = [0,2,4,8,8,0,2,10]
    // FIFO remove o 0 (primeiro inserido)
    {
        CacheConfig config(1, 8, 4);
        auto cache = createCache("F", config);

        cache->execute(0, 0);
        cache->execute(0, 2);
        cache->execute(0, 4);
        cache->execute(0, 8);
        cache->execute(0, 8);
        cache->execute(0, 0);
        cache->execute(0, 2);
        cache->execute(0, 10);

        std::cout << "FIFO must have replaced 0" << "\n";
        ASSERT_EQUAL(MISS, cache->execute(0, 0));

        std::cout << "----------------------------------" << "\n"; 
    }

    // TESTE 4
    // Lista = [0,2,4,8,8,0,8,4,2,10]
    // FIFO remove 0 (sempre o mais antigo)
    {
        CacheConfig config(1, 8, 4);
        auto cache = createCache("F", config);

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

        std::cout << "FIFO must have replaced 0" << "\n";
        ASSERT_EQUAL(MISS, cache->execute(0, 0));

        std::cout << "----------------------------------" << "\n"; 
    }

}