#include "src/emulator/util.h"

#include <cstdint>
#include <gtest/gtest.h>


TEST(Util, OverflowingAdd) {
    uint8_t a0 = 0xFF;
    uint8_t b0 = 0x01;
    auto [c0, overflowed0] = OverflowingAdd(a0, b0);
    EXPECT_EQ(overflowed0[7], true);
    EXPECT_EQ(c0, 0x00);

    uint8_t a1 = 0xFE;
    uint8_t b1 = 0x01;
    auto [c1, overflowed1] = OverflowingAdd(a1, b1);
    EXPECT_EQ(overflowed1[7], false);
    EXPECT_EQ(c1, 0xFF);
}


#include <gtest/gtest.h>

TEST(Util, GetBitRange) {
    uint8_t v = 0b11110000;

    auto r0 = GetBitRange<uint8_t>(v, 0, 3);
    EXPECT_EQ(r0, 0b00000000);

    auto r1 = GetBitRange<uint8_t>(v, 4, 7);
    EXPECT_EQ(r1, 0b00001111);

    auto r2 = GetBitRange<uint8_t>(0b10101011, 0, 3);
    EXPECT_EQ(r2, 0b00001011);

    auto r3 = GetBitRange<uint8_t>(0b10101011, 4, 7);
    EXPECT_EQ(r3, 0b00001010);
}