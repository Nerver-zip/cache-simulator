#pragma once

#include "test_framework.h"
#include "../../src/factory/factory.h"

inline void test_random() {
    #define MISS false
    #define HIT true
    
    {
        CacheConfig config(2, 8, 4);
        auto cache = createCache("R", config);

        // Teste de hit/miss
        // Dados: 2,2,4,4,1,1,7

        ASSERT_EQUAL(MISS, cache->execute(0, 2));
        ASSERT_EQUAL(HIT, cache->execute(0, 2));
        ASSERT_EQUAL(MISS, cache->execute(0, 4));
        ASSERT_EQUAL(HIT, cache->execute(0, 4));
        ASSERT_EQUAL(MISS, cache->execute(1, 1));
        ASSERT_EQUAL(HIT, cache->execute(1, 1));
        ASSERT_EQUAL(MISS, cache->execute(1, 7));
        ASSERT_EQUAL(1LL * 3, cache->getHits());
        ASSERT_EQUAL(1LL * 4, cache->getMisses().total);

        std::cout << "----------------------------------" << "\n";
    }

    {
        CacheConfig config(4, 4, 4);
        auto cache = createCache("R", config);

        // Teste de hit/miss
        // Dados: 16,4,8,16,4,20,32

        ASSERT_EQUAL(MISS, cache->execute(0, 16));
        ASSERT_EQUAL(MISS, cache->execute(0, 4));
        ASSERT_EQUAL(MISS, cache->execute(0, 8));
        ASSERT_EQUAL(HIT, cache->execute(0, 16));
        ASSERT_EQUAL(HIT, cache->execute(0, 4));
        ASSERT_EQUAL(MISS, cache->execute(0, 20));
        ASSERT_EQUAL(MISS, cache->execute(0, 32));
        ASSERT_EQUAL(1LL * 2, cache->getHits());
        ASSERT_EQUAL(1LL * 5, cache->getMisses().total);
    }
}
