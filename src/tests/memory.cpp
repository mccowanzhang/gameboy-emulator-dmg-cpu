#include "src/emulator/memory.h"

#include <gtest/gtest.h>

TEST(memory, test1) {
    auto memory = Memory();
    EXPECT_EQ(memory.Read8(0), 0x00);
    EXPECT_EQ(memory.Read8(1), 0x00);
    EXPECT_EQ(memory.Read16(0), 0x00);
    EXPECT_EQ(memory.Read16(1), 0x00);

    memory.Write8(1, 0xFF);
    EXPECT_EQ(memory.Read8(0), 0x00);
    EXPECT_EQ(memory.Read8(1), 0xFF);
    EXPECT_EQ(memory.Read16(0), 0xFF00);
    EXPECT_EQ(memory.Read16(1), 0x00FF);

    memory.Reset();
    EXPECT_EQ(memory.Read8(0), 0x00);
    EXPECT_EQ(memory.Read8(1), 0x00);
    EXPECT_EQ(memory.Read16(0), 0x00);
    EXPECT_EQ(memory.Read16(1), 0x00);

    memory.Write16(1, 0xFFEE);
    EXPECT_EQ(memory.Read8(0), 0x00);
    EXPECT_EQ(memory.Read8(1), 0xEE);
    EXPECT_EQ(memory.Read8(2), 0xFF);
    EXPECT_EQ(memory.Read16(0), 0xEE00);
    EXPECT_EQ(memory.Read16(1), 0xFFEE);
    EXPECT_EQ(memory.Read16(2), 0x00FF);
}