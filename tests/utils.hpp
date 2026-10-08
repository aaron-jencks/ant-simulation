#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <random>

std::mt19937 rng(std::random_device{}());
std::uniform_real_distribution<float> rand_float(0, 1000);

#endif