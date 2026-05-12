#include "src/emulator/util.h"

#include <cstdint>
#include <gtest/gtest.h>


TEST(Util, OverflowingAdd) {
    uint8_t a0 = 0xFF;
    uint8_t b0 = 0x01;
    uint8_t c0;
    bool overflowed = OverflowingAdd(a0, b0, c0);
    EXPECT_EQ(overflowed, true);
    EXPECT_EQ(c0, 0x00);

    uint8_t a1 = 0xFE;
    uint8_t b1 = 0x01;
    uint8_t c1;
    overflowed = OverflowingAdd(a1, b1, c1);
    EXPECT_EQ(overflowed, false);
    EXPECT_EQ(c1, 0xFF);

    int8_t a2 = 0xD;
    int8_t b2 = 0x1;
    int8_t c2;
    overflowed = OverflowingAdd(a2, b2, c2);
    EXPECT_EQ(overflowed, false);
    EXPECT_EQ(c2, 0xE);

    int8_t a3 = 0x7F;
    int8_t b3 = 0x1;
    int8_t c3;
    overflowed = OverflowingAdd(a3, b3, c3);
    EXPECT_EQ(overflowed, true);
    EXPECT_EQ(c3, -0x80);

    int8_t a4 = -0x80;
    int8_t b4 = -0x1;
    int8_t c4;
    overflowed = OverflowingAdd(a4, b4, c4);
    EXPECT_EQ(overflowed, true);
    EXPECT_EQ(c4, 0x7F);

}