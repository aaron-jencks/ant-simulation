#include "utils.hpp"

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>


std::vector<std::uint8_t> load_file_bytes(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<std::uint8_t> data;
    char byte;

    while (file.get(byte)) {
        data.push_back(static_cast<std::uint8_t>(byte));
    }

    if (file.bad() || !file.eof()) {
        throw std::runtime_error("Failed reading file: " + filename);
    }

    return data;
}

std::vector<std::uint8_t> generate_random_data(std::size_t len) {
    auto data = std::vector<std::uint8_t>(len);
    for(auto& byte : data)
        byte = static_cast<std::uint8_t>(rand_byte(rng));
    return data;
}