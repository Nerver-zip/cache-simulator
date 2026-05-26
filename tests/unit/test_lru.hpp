#pragma once

#include "test_framework.h"
#include "../../src/caches/LRU.h"



inline void test_lru(){
    #define MISS false
    #define HIT true

    // Tamanho do bloco não importa aqui
    // Definimos uma cache de 2 conjuntos de 4 vias cada
    CacheConfig config(2, 4, 8);
    LRU cache(config);

    // Teste de hit/miss
    // Dados: 2,4,6,8,2,10,4
    // Deve dar um hit no 2
    // Expulsar o 4 quando colocar 10
    // E assim dando miss no 4, o que valida o LRU
    // já que expulsamos o correto
    
    ASSERT_EQUAL(MISS, cache.execute(0, 2));
    ASSERT_EQUAL(MISS, cache.execute(0, 4));
    ASSERT_EQUAL(MISS, cache.execute(0, 6));
    ASSERT_EQUAL(MISS, cache.execute(0, 8));
    ASSERT_EQUAL(HIT,  cache.execute(0, 2));
    ASSERT_EQUAL(MISS, cache.execute(0, 10));
    ASSERT_EQUAL(MISS, cache.execute(0, 4));

    // --- Colocar mais um teste desses
    // E depois um testando a saída final
}
