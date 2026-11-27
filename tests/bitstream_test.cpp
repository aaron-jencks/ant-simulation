#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <vector>

#include <engine/images/parsing/bitstream.hpp>

#include "doctest.h"
#include "utils.hpp"

#define GENERATE_BYTE_MASK(b, n) (static_cast<std::uint32_t>(b) << (n << 3))

TEST_SUITE_BEGIN("BitStream");

TEST_CASE("Verify Bounds Checking") {
    auto data = generate_random_data(100);
    auto sample_reader = engine::images::parsing::BitStream(
        data
    );
    std::uint32_t sample = sample_reader.readBits(8);
    REQUIRE_EQ(sample, data[0]);
    REQUIRE_THROWS_AS(sample_reader.readBits(33), const std::invalid_argument&);
    for(std::size_t i = 1; i < 97; i++) {
        REQUIRE_EQ(sample_reader.readBits(8), data[i]);
    }
    REQUIRE_THROWS_AS(sample_reader.readBits(32), const std::runtime_error&);
}

TEST_CASE("Verify Bit Count Calculation") {
    auto data = generate_random_data(100);
    auto sample_reader = engine::images::parsing::BitStream(
        data
    );
    REQUIRE_EQ(sample_reader.length(), 800u);
    sample_reader.readBits(8);
    REQUIRE_EQ(sample_reader.length(), 792u);
    sample_reader.readBits(1);
    REQUIRE_EQ(sample_reader.length(), 791u);
    sample_reader.readBits(2);
    REQUIRE_EQ(sample_reader.length(), 789u);
}

TEST_CASE("Verify Data Integrity") {
    auto data = generate_random_data(100);
    auto sample_reader = engine::images::parsing::BitStream(
        data
    );
    std::uint32_t sample = sample_reader.readBits(8);
    REQUIRE_EQ(sample, data[0]);
    sample = sample_reader.readBits(16);
    std::uint32_t expected = GENERATE_BYTE_MASK(data[2], 1) + data[1];
    REQUIRE_EQ(sample, expected);
    expected = GENERATE_BYTE_MASK(data[5], 2) + GENERATE_BYTE_MASK(data[4], 1) + data[3];
    sample = sample_reader.readBits(24);
    REQUIRE_EQ(sample, expected);
    sample = sample_reader.readBits(32);
    expected = GENERATE_BYTE_MASK(data[9], 3) + GENERATE_BYTE_MASK(data[8], 2) + GENERATE_BYTE_MASK(data[7], 1) + data[6];
    REQUIRE_EQ(sample, expected);
}

TEST_CASE("Verify Big-Endianness") {
    std::uint32_t target = 0xdeadbeef;
    auto test_data = std::vector<std::uint8_t>({
        0xde, 0xad, 0xbe, 0xef
    });
    auto test_reader = engine::images::parsing::BitStream(test_data);
    REQUIRE_EQ(target, test_reader.readLong());
}

inline void assertBytesEq(engine::images::parsing::BitStream stream, std::vector<std::uint8_t> expected) {
    std::uint8_t temp;
    for(auto expected : expected) {
        temp = stream.readByte();
        REQUIRE_EQ(temp, expected);
    }
}

TEST_CASE("Real-world data") {
    auto file_data = load_file_bytes("tests/assets/sample-png.png");
    auto sample_reader = engine::images::parsing::BitStream(file_data);
    assertBytesEq(
        sample_reader,
        std::vector<std::uint8_t>({
            0x89,               // First byte is always 0x89
            0x50, 0x4e, 0x47,   // Followed by the 3 bytes "PNG"
            0x0d, 0x0a,         // DOS style line ending
            0x1a,               // Something to stop the display of the file in DOS
            0x0a                // UNIX style line ending
        })
    );
}

TEST_SUITE_END();
