#include "src/emulator/op/bit.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"
#include "src/tests/test_base.h"

#include <gtest/gtest.h>

#include <memory>

class BITTest : public ::testing::Test {
protected:
    Memory memory;
    CPU cpu{memory};
};

TEST_F(BITTest, CP_NE) {
    std::array<uint8_t, 1> program{
        0b10111000, // CP B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.B = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, CP_EQ) {
    std::array<uint8_t, 1> program{
        0b10111001, // CP C
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.C = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2);
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}


TEST_F(BITTest, CP_HLI) {
    std::array<uint8_t, 1> program{
        0b10111110, // CP (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, CP_N) {
    std::array<uint8_t, 2> program{
        0b11111110, // CP_N
        kVal1,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal2);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, AND) {
    std::array<uint8_t, 1> program{
        0b10100000, // AND B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.B = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 & kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}


TEST_F(BITTest, AND_HLI) {
    std::array<uint8_t, 1> program{
        0b10100110, // AND (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 & kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, AND_N) {
    std::array<uint8_t, 2> program{
        0b11100110, // AND_N
        kVal1,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 & kVal2);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, OR) {
    std::array<uint8_t, 1> program{
        0b10110000, // OR B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.B = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 | kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}


TEST_F(BITTest, OR_HLI) {
    std::array<uint8_t, 1> program{
        0b10110110, // OR (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 | kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, OR_N) {
    std::array<uint8_t, 2> program{
        0b11110110, // OR_N
        kVal1,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 | kVal2);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, XOR) {
    std::array<uint8_t, 1> program{
        0b10101000, // XOR B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.B = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 ^ kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}


TEST_F(BITTest, XOR_HLI) {
    std::array<uint8_t, 1> program{
        0b10101110, // XOR (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 ^ kVal2);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}

TEST_F(BITTest, XOR_N) {
    std::array<uint8_t, 2> program{
        0b11101110, // XOR_N
        kVal1,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1 ^ kVal2);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
}
