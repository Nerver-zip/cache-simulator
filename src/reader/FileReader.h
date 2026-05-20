#pragma once

#include <iostream>
#include <fstream>

class FileReader {
private:
    std::ifstream file;

public:
    FileReader(const std::string& filename);

    bool nextInt32(uint32_t& value);
};
