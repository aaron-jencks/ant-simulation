#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <limits>
#include <type_traits>

namespace AntSim {
    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    random_range(T lower, T upper) {
        double random_number = static_cast<double>(rand()) / static_cast<double>(std::numeric_limits<int>::max());
        return static_cast<T>(random_number * (static_cast<double>(upper) - static_cast<double>(lower)) + static_cast<double>(lower));
    }

    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    random_variation(T variation) {
        return random_range(-variation, variation);
    }
}

#endif
