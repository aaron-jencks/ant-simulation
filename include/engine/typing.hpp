#ifndef TYPING_H
#define TYPING_H

#include <type_traits>

namespace engine {
    template <typename T>
    concept Numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;
}

#endif
