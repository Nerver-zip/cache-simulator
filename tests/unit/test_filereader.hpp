#pragma once

#include <array>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include "../../src/reader/FileReader.h"
#include "test_framework.h"

inline void test_filereader(){

    constexpr std::array<std::pair<std::string_view, std::string_view>, 4> paths = {{
        {"tests/workloads/bin_100.bin","tests/workloads/bin_100.txt"},
        {"tests/workloads/bin_1000.bin","tests/workloads/bin_1000.txt"},
        {"tests/workloads/bin_10000.bin","tests/workloads/bin_10000.txt"},
        {"tests/workloads/vortex.in.sem.persons.bin","tests/workloads/vortex.in.sem.persons.txt"}
    }};

    uint32_t from_bin;
    uint32_t from_txt;

    for (const auto& [bin_path, txt_path] : paths) {
        std::ifstream txt_file(txt_path.data());
        
        if (!txt_file) {
            throw std::runtime_error("Error: could not open text file");              
        }
        
        FileReader reader(bin_path.data());

        while (reader.nextInt32(from_bin) && txt_file >> from_txt) 
        {
            uint32_t converted_bin = (from_bin);
            ASSERT_EQUAL_SILENT(converted_bin, from_txt, converted_bin, from_txt);
        }    
    }
}
