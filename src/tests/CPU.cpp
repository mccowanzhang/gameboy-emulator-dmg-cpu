#include "src/emulator/CPU.h"

#include "src/emulator/memory.h"

#include <gtest/gtest.h>

TEST(CPU, registers) {
    Memory memory;
    CPU cpu(memory);
    Registers registers = cpu.GetRegisters();

    EXPECT_EQ(registers.GetFlag(Flag::Z_FLAG), false);
    EXPECT_EQ(registers.GetFlag(Flag::N_FLAG), false);
    EXPECT_EQ(registers.GetFlag(Flag::H_FLAG), false);
    EXPECT_EQ(registers.GetFlag(Flag::C_FLAG), false);
    EXPECT_EQ(registers.AF(), 0x0000);
    EXPECT_EQ(registers.BC(), 0x0000);
    EXPECT_EQ(registers.DE(), 0x0000);
    EXPECT_EQ(registers.HL(), 0x0000);
    EXPECT_EQ(registers.A, 0x00);
    EXPECT_EQ(registers.B, 0x00);
    EXPECT_EQ(registers.C, 0x00);
    EXPECT_EQ(registers.D, 0x00);
    EXPECT_EQ(registers.E, 0x00);
    EXPECT_EQ(registers.H, 0x00);
    EXPECT_EQ(registers.L, 0x00);

    // should not change cpu registers
    registers.A = 0x01;
    Registers registers2 = cpu.GetRegisters();
    EXPECT_EQ(registers2.A, 0x00);
}

TEST(CPU, ADD) {
    Memory memory;
    CPU cpu(memory);
    
    // TODO: test ADD
    Registers registers = cpu.GetRegisters();
}