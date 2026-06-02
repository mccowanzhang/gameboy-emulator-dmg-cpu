#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

#include <limits>
#include <memory>

TEST(ADD, ADD) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    cpu.memory.Write8(0x0000, 0b10000000); // ADD B to A
    cpu.registers.A = 3;
    cpu.registers.B = 5;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, 8);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST(ADD, ADD_HLI) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    cpu.memory.Write8(0x0000, 0b10000110); // ADD HLI to A
    cpu.registers.A = 3;
    uint8_t val = 5;
    uint16_t addr = 0x0040;
    memory.Write8(addr, val);
    cpu.registers.SetHL(addr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, 8);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST(ADD, ADC) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    std::array<uint8_t, 2> program{
        0b10000000, // ADD B to A
        0b10001001, // ADC C to A
    };
    cpu.memory.WriteProgram(0x0000, program);
    cpu.registers.A = std::numeric_limits<uint8_t>::max();
    cpu.registers.B = 1;
    cpu.Step(); // ADD B to A
    EXPECT_EQ(cpu.registers.A, 0);
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::C_FLAG));
    cpu.registers.C = 4;
    cpu.Step(); // ADC C to A
    EXPECT_EQ(cpu.registers.A, 5); // 0 + 4 + 1 (C_FLAG)
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
    // TODO: TEST HLI
}

TEST(ADD, ADC_HLI) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    cpu.memory.Write8(0x0000, 0b10001110); // ADC HLI to A
    cpu.registers.A = 3;
    cpu.registers.SetFlag(Flag::C_FLAG, true);
    uint8_t val = 5;
    uint16_t addr = 0x0040;
    memory.Write8(addr, val);
    cpu.registers.SetHL(addr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, 9);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
    // TODO: TEST HLI
}