#pragma once

#include <array>
#include <limits> 
#include <tuple>
#include <type_traits>

template <typename T>
std::pair<T, std::array<bool, sizeof(T) * 8>> OverflowingAdd(T a, T b) {
    static_assert(std::is_unsigned_v<T>,
                  "Carry tracking only makes sense for unsigned types");

    constexpr size_t kBits = sizeof(T) * 8;
    std::array<bool, kBits> carry_per_bit{};
    T result = 0;
    bool carry = false;

    for (size_t bit = 0; bit < kBits; ++bit) {
        bool a_bit = (a >> bit) & 1;
        bool b_bit = (b >> bit) & 1;

        bool sum_bit = a_bit ^ b_bit ^ carry;

        bool carry_out =
            (a_bit && b_bit) ||
            (a_bit && carry) ||
            (b_bit && carry);

        if (sum_bit) {
            result |= (T{1} << bit);
        }

        carry_per_bit[bit] = carry_out;
        carry = carry_out;
    }

    return {result, carry_per_bit};
}

template <typename T>
T GetBitRange(T value, uint8_t low, uint8_t high) { // low, high inclusive
    static_assert(std::is_integral_v<T>, "T must be integral");
    constexpr uint8_t kBits = sizeof(T) * 8;
    if (low > high) {
        throw std::invalid_argument("low must be <= high");
    }
    if (high >= kBits) {
        throw std::out_of_range("bit range exceeds type width");
    }
    T mask = ((T{1} << (high - low + 1)) - 1) << low;
    return (value & mask) >> low;
}

inline uint16_t Promote(uint8_t lsb, uint8_t msb) {
    return (static_cast<uint16_t>(msb) << 8) | lsb;
}

inline uint16_t PromoteH(uint8_t val) {
    return Promote(val, 0xFF);
}

inline uint8_t LSB(uint16_t val) {
    return static_cast<uint8_t>(val & 0xFF);
}

inline uint8_t MSB(uint16_t val) {
    return static_cast<uint8_t>(val >> 8);
}
