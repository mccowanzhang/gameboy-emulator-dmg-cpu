#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

TEST(LD, LD_r_r) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    std::array<uint8_t, 1> program{
        0b01000001 // LD B, C
    };
    cpu.memory.WriteProgram(0x0000, program);
    cpu.registers.B = 3;
    cpu.registers.C = 5;
    cpu.Step();
    EXPECT_EQ(cpu.registers.B, cpu.registers.C);
    EXPECT_EQ(cpu.registers.B, 5);
}