#include "src/emulator/op/sub.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

#include <memory>

class SUBTest : public ::testing::Test {
protected:
    static constexpr uint8_t kVal1 = 3;
    static constexpr uint8_t kVal2 = 5;
    static constexpr uint16_t kAddr = 0x0040;
    static constexpr uint16_t kStartPC = 0x0000;

    Memory memory;
    CPU cpu{memory};
};

TEST_F(SUBTest, SUB) {
    std::array<uint8_t, 1> program{
        0b10010000, // SUB B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.B = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2 - kVal1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(SUBTest, SUB_HLI) {
    std::array<uint8_t, 1> program{
        0b10010110, // SUB (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2 - kVal1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(SUBTest, SUB_N) {
    std::array<uint8_t, 2> program{
        0b11010110, // SUB_N
        kVal1,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2 - kVal1);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(SUBTest, SBC) {
    std::array<uint8_t, 1> program{
        0b10011000, // SBC B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.B = kVal1;
    cpu.registers.SetFlag(Flag::C_FLAG, true);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2 - kVal1 - 1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(SUBTest, SBC_HLI) {
    std::array<uint8_t, 1> program{
        0b10011110, // SBC (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.registers.SetFlag(Flag::C_FLAG, true);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2 - kVal1 - 1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(SUBTest, SBC_N) {
    std::array<uint8_t, 2> program{
        0b11011110, // SBC_N
        kVal1,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.SetFlag(Flag::C_FLAG, true);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2 - kVal1 - 1);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}
