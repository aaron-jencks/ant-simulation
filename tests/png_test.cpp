#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <vector>

#include <engine/images/parsing/bitstream.hpp>
#include <engine/images/parsing/png.hpp>
#include <engine/utils/crc32.hpp>

#include "doctest.h"
#include "utils.hpp"

inline engine::images::parsing::BitStream create_bitstream_from_vector(std::vector<std::uint8_t> data) {
    return engine::images::parsing::BitStream(data);
}

TEST_CASE("Check Header Contents") {
    SUBCASE("Valid Header") {
        auto test_data = std::vector<std::uint8_t>({
            0x89,
            0x50, 0x4e, 0x47,
            0x0d, 0x0a,
            0x1a,
            0x0a
        });
        auto test_reader = engine::images::parsing::BitStream(test_data);
        REQUIRE(check_file_header(test_reader));
    }

    SUBCASE("Too little data") {
        auto test_data = std::vector<std::uint8_t>({
            // 0x89,
            0x50, 0x4e, 0x47,
            0x0d, 0x0a,
            0x1a,
            0x0a
        });
        auto test_reader = engine::images::parsing::BitStream(test_data);
        REQUIRE_FALSE(check_file_header(test_reader));
    }

    SUBCASE("Corrupt magic number") {
        auto test_data = std::vector<std::uint8_t>({
            0x89,
            0x50, 0x4e, 0x47,
            0x0d, 0x0a,
            0x1a,
            0x0a
        });
        auto test_reader = engine::images::parsing::BitStream(test_data);
        for(std::size_t i = 0; i < 8; i++) {
            ++test_data[i];
            REQUIRE_FALSE(check_file_header(test_reader));
            test_reader.reset();
            --test_data[i];
        }
        REQUIRE(check_file_header(test_reader));
    }
}

inline void inject_data(std::vector<std::uint8_t>& buff, const std::size_t offset, const std::uint32_t data) {
    for(std::size_t i = 0; i < 4; i++) {
        buff[offset + i] = static_cast<std::uint8_t>(data >> ((4 - i - 1) * 8));
    }
}

TEST_CASE("Chunk Contents") {
    auto test_data = generate_random_data(1000);
    auto test_reader = engine::images::parsing::BitStream(test_data);
    std::uint32_t length = 64, data_type = 5, crc = 54;
    inject_data(test_data, 0, length);
    inject_data(test_data, 4, data_type);
    inject_data(test_data, length + 8, crc);
    auto chunk = read_file_chunk(test_reader);
    REQUIRE_EQ(chunk.length, length);
    CHECK_EQ(chunk.type, data_type);
    CHECK_EQ(chunk.crc, crc);
    REQUIRE_EQ(chunk.data.size(), length);
    for(std::size_t i = 0; i < length; i++) {
        CHECK_EQ(chunk.data[i], test_data[i + 8]);
    }
}

TEST_CASE("Verify CRC") {
    auto test_data = generate_random_data(1000);
    auto test_reader = engine::images::parsing::BitStream(test_data);
    std::uint32_t length = 64, data_type = 5, crc = 54;
    inject_data(test_data, 0, length);
    inject_data(test_data, 4, data_type);
    inject_data(test_data, length + 8, crc);
    auto chunk = read_file_chunk(test_reader);
    auto first_data_element = test_data.begin() + 8;
    std::uint32_t computed_crc = engine::utils::compute_crc32(
        std::span<std::uint8_t>(first_data_element, first_data_element + length) 
    );
    CHECK_NE(computed_crc, crc);
    inject_data(test_data, length + 8, computed_crc);
    test_reader.reset();
    chunk = read_file_chunk(test_reader);
    REQUIRE(chunk.verify_crc());
}