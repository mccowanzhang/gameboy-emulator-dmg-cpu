#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

#include <limits>
#include <memory>

class ADDTest : public ::testing::Test {
protected:
    static constexpr uint8_t kVal1 = 3;
    static constexpr uint8_t kVal2 = 5;
    static constexpr uint16_t kAddr = 0x0040;
    static constexpr uint16_t kStartPC = 0x0000;

    Memory memory;
    CPU cpu{memory};
};

TEST_F(ADDTest, ADD) {
    cpu.memory.Write8(kStartPC, 0b10000000); // ADD B to A
    cpu.registers.A = kVal1;
    cpu.registers.B = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, 8);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(ADDTest, ADD_HLI) {
    cpu.memory.Write8(kStartPC, 0b10000110); // ADD HLI to A
    cpu.registers.A = kVal1;
    uint8_t val = kVal2;
    memory.Write8(kAddr, val);
    cpu.registers.SetHL(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, 8);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(ADDTest, ADD_N) {
    std::array<uint8_t, 2> program{
        0b11000110, // ADD_N
        kVal2,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 + kVal2);
    EXPECT_EQ(cpu.registers.PC, 0x2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(ADDTest, ADC) {
    std::array<uint8_t, 2> program{
        0b10000000, // ADD B to A
        0b10001001, // ADC C to A
    };
    cpu.memory.WriteProgram(kStartPC, program);
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

TEST_F(ADDTest, ADC_HLI) {
    cpu.memory.Write8(kStartPC, 0b10001110); // ADC HLI to A
    cpu.registers.A = kVal1;
    cpu.registers.SetFlag(Flag::C_FLAG, true);
    uint8_t val = kVal2;
    memory.Write8(kAddr, val);
    cpu.registers.SetHL(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, 9);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
    // TODO: TEST HLI
}