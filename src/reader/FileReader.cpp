#include "FileReader.h"

FileReader::FileReader(const std::string& filename) {
    file.open(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Error: Could not open file: " + filename
        );
    }
}

bool FileReader::nextInt32(uint32_t& value) {
    uint8_t bytes[4];

    if (!file.read(reinterpret_cast<char*>(bytes), 4)) {
        return false;
    }

    value =
        (uint32_t(bytes[0]) << 24) |
        (uint32_t(bytes[1]) << 16) |
        (uint32_t(bytes[2]) << 8)  |
        uint32_t(bytes[3]);

    return true;
}
