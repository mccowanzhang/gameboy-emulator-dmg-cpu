#include "src/emulator/memory.h"

#include <gtest/gtest.h>

TEST(Memory, Memory) {
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

    std::array<uint8_t, 0x4> program{
        0x01,
        0x02,
        0x03,
        0x04,
    };
    memory.WriteProgram(0x00, program);
    for (size_t i = 0; i < program.size(); ++i) {
        EXPECT_EQ(memory.Read8(i), program[i]);
    }
}