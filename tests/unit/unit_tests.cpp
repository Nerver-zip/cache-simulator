#include "test_framework.h"
#include "test_decoder.hpp"
#include "test_sanitizer.hpp"
#include "test_filereader.hpp"

int main() {
    RUN_TEST(test_decoder);
    RUN_TEST(test_sanitizer);
    RUN_TEST(test_filereader);

    TEST_SUMMARY(); 
}
