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
     
    };


    std::vector<TestCase> validCases = {
            
    };

    for(const auto& test : invalidCases){
        ASSERT_ANY_THROW_VERBOSE(Sanitizer::sanitize(test.argc, test.argv.data()), test.argc, test.argv.data());
    }

    for(const auto& test : validCases){
        ASSERT_NO_THROW_VERBOSE(Sanitizer::sanitize(test.argc, test.argv.data()), test.argc, test.argv.data());
    }
}
