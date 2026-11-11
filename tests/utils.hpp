#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <cstdint>
#include <random>

inline std::mt19937 rng(std::random_device{}());
inline std::uniform_real_distribution<float> rand_float(0, 1000);
inline std::uniform_int_distribution<std::uint8_t> rand_byte(0, 255);

#endif