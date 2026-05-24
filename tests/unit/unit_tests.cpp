#include <iostream>
#include "test_framework.h"
#include "test_decoder.hpp"

int main() {
    RUN_TEST(test_decoder);

    std::cout << "\n";
    std::cout << passed << "/" << tests << " tests passed\n";
}
