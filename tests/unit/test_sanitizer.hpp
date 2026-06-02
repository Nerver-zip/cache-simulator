#pragma once

#include "../../src/sanitizer/sanitizer.h"
#include "test_framework.h"
#include <vector>

struct TestCase {
    int argc;
    std::vector<const char*> argv;
};

inline void test_sanitizer(){

    std::vector<TestCase> invalidCases = {
        {
            1,
            {"./cache_simulator"}
        },
        {
            2,
            {"./cache_simulator", "SIXSEVEN"}
        },
        {
            7,
            {"./cache_simulator", "31", "4", "32", "L", "1", "exemplo.bin"}
        }, // nsets não é potência de 2
        {
            7,
            {"./cache_simulator", "32", "abc", "32", "L", "1", "exemplo.bin"}
        }, // assoc inválido
        {
            7,
            {"./cache_simulator", "32", "4", "33", "L", "1", "exemplo.bin"}
        }, // bsize não é potência de 2
        {
            7,
            {"./cache_simulator", "32", "4", "32", "X", "1", "exemplo.bin"}
        }, // política inválida
        {
            7,
            {"./cache_simulator", "32", "4", "32", "L", "67", "exemplo.bin"}
        }, // flag inválida
        {
            7,
            {"./cache_simulator", "32", "4", "32", "L", "0", "exemplo.js"}
        }, // arquivo invalido
        {
            7,
            {"./cache_simulator", "536870912", "1048576", "32", "L", "1", ".bin"}
        }, // tamanho grande demais
        {
            7,
            {"./cache_simulator", "1048576", "1048576", "32", "L", "1", "exemplo.bin"}
        } // tamango grande demais
    };


    std::vector<TestCase> validCases = {
        {
            7,
            {"./cache_simulator", "32", "4", "32", "L", "1", "exemplo.bin"}
        },
        {
            7,
            {"./cache_simulator", "64", "8", "64", "F", "0", "exemplo2.bin"}
        },
        {
            7,
            {"./cache_simulator", "1024", "16", "4", "L", "1", "exemplo3.bin"}
        },
        {
            7,
            {"./cache_simulator", "4096", "1024", "128", "L", "1", ".bin"}
        },
        {
            7,
            {"./cache_simulator", "1024", "4096", "256", "L", "1", "aocII.bin"}
        }
    };
    
    int i = 0;
    for(const auto& test : invalidCases){
        std::cout << i++ << "\n";
        ASSERT_ANY_THROW(Sanitizer::sanitize(test.argc, test.argv.data()));
    }
    
    std::cout << "----------------------------------" << "\n"; 

    for(const auto& test : validCases){
        ASSERT_NO_THROW(Sanitizer::sanitize(test.argc, test.argv.data()));
    }
}
