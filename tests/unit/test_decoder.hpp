#pragma once

#include <array>
#include <cstdint>
#include "../../src/decode/decoder.h"
#include "../../src/caches/ICache.h"
#include "test_framework.h"

inline void test_decoder() {
    struct TestCase {
        uint32_t address;
        CacheConfig config;
        std::pair<uint32_t, uint32_t> expected;
    };

    // Endereço, configuração da cache, valores esperados de índice e tag
    constexpr std::array<TestCase, 20> testcases = {{
        {0x11110001, {1,     1,     2},    {0,    286326785}},
        {0xCAFEBABE, {2,     1,     4},    {0,    1702845791}},
        {0xDEADBEEF, {4,     2,     8},    {3,    466991069}},
        {0x12345678, {8,     2,    16},    {4,    19088743}},
        {0x87654321, {16,    4,    32},    {8,    35493132}},
        {0x0F0F0F0F, {32,    4,    64},    {3,    1973790}},
        {0xF0F0F0F0, {64,    8,   128},    {30,   7895160}},
        {0xAAAAAAAA, {128,   1,    16},    {42,   22369621}},
        {0x55555555, {256,   2,    32},    {170,  2796202}},
        {0xABCDEF12, {512,   4,    64},    {452,  1407421}},
        {0x13579BDF, {1024,  8,   128},    {891,  39612}},
        {0x2468ACE0, {2048, 16,   256},    {718,  18641}},
        {0xFFFFFFFF, {4096,  1,    64},    {4095, 1048575}},
        {0x00000000, {8192,  2,   128},    {0,    0}},
        {0x80000000, {16,    4,   256},    {0,    33554432}},
        {0x7FFFFFFF, {32,    8,   512},    {31,   8388607}},
        {0xFEEDC0DE, {64,    16, 1024},   {13,   4176752}},
        {0xB16B00B5, {128,   1, 2048},    {53,   23254529}},
        {0xC001D00D, {256,   2, 4096},    {6,    6291688}},
        {0x42A7F91C, {512,   4, 8192},    {71,   546047}},
    }};

    for (int i = 1; const auto& tc : testcases) {
        std::cout << "Case #" << i++ << "\n";
        
        const auto decoded = Decoder::decodeAddress(tc.address, tc.config); 
        
        ASSERT_EQUAL_VERBOSE(
            tc.expected,
            decoded,
            tc.expected,
            decoded,
            tc.address,
            tc.config
        );
    }
}
