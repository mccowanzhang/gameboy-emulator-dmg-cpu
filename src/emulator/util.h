#pragma once

#include <limits> 
#include <type_traits>

template <typename T>
bool OverflowingAdd(T a, T b, T& res) {
    static_assert(std::is_integral_v<T>, "Must be integral type");

    res = a + b;

    if constexpr(std::is_signed_v<T>) {
        return
            (b > 0 && a > std::numeric_limits<T>::max() - b) ||
            (b < 0 && a < std::numeric_limits<T>::min() - b);
    } else {
        return res < a;
    }
}
