#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

class LDTest : public ::testing::Test {
protected:
    static constexpr uint8_t kVal1 = 3;
    static constexpr uint8_t kVal2 = 5;
    static constexpr uint16_t kBigVal1 = 0x1234;
    static constexpr uint16_t kStartPC = 0x0000;
    static constexpr uint16_t kAddr = 0x0040;
    static constexpr uint16_t kBigAddr = 0x1040;

    Memory memory;
    CPU cpu{memory};
};

TEST_F(LDTest, LD_R_R) {
    std::array<uint8_t, 1> program{
        0b01000001 // LD B, C
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.B = kVal1;
    cpu.registers.C = kVal2;
    cpu.Step();
    EXPECT_EQ(cpu.registers.B, cpu.registers.C);
    EXPECT_EQ(cpu.registers.B, kVal2);
}

TEST_F(LDTest, LD_HLI_R) {
    std::array<uint8_t, 1> program{
        0b01110011 // LD to HLI from E
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.E = kVal1;
    cpu.registers.SetHL(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal1);
}

TEST_F(LDTest, LD_R_HLI) {
    std::array<uint8_t, 1> program{
        0b01010110 // LD to D from HLI
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.D = kVal1;
    memory.Write8(kAddr, kVal2);
    cpu.registers.SetHL(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.D, kVal2);
}

TEST_F(LDTest, LD_R_N) {
    std::array<uint8_t, 2> program{
        0b00000110, // LD to B from N
        kVal2,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.Step();
    EXPECT_EQ(cpu.registers.B, kVal2);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
}

TEST_F(LDTest, LD_HLI_N) {
    std::array<uint8_t, 2> program{
        0b00110110, // LD to HLI from N
        kVal2,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetHL(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal2);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
}

TEST_F(LDTest, LD_BCI_A) {
    std::array<uint8_t, 1> program{
        0b00000010, // LD to BCI from A
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.registers.SetBC(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal1);
}

TEST_F(LDTest, LD_A_BCI) {
    std::array<uint8_t, 1> program{
        0b00001010, // LD to A from BCI
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetBC(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1);
}

TEST_F(LDTest, LD_DEI_A) {
    std::array<uint8_t, 1> program{
        0b00010010, // LD to DEI from A
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.registers.SetDE(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal1);
}

TEST_F(LDTest, LD_A_DEI) {
    std::array<uint8_t, 1> program{
        0b00011010, // LD to A from DEI
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetDE(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1);
}

TEST_F(LDTest, LD_HLPLUSI_A) {
    std::array<uint8_t, 1> program{
        0b00100010, // LD to HLPLUSI from A
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.registers.SetHL(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.HL(), kAddr + 1);
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal1);
}

TEST_F(LDTest, LD_A_HLPLUSI) {
    std::array<uint8_t, 1> program{
        0b00101010, // LD to A from HLPLUSI
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1);
    EXPECT_EQ(cpu.registers.HL(), kAddr + 1);
}

TEST_F(LDTest, LD_HLMINUSI_A) {
    std::array<uint8_t, 1> program{
        0b00110010, // LD to HLMINUSI from A
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.registers.SetHL(kAddr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.HL(), kAddr - 1);
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal1);
}

TEST_F(LDTest, LD_A_HLMINUSI) {
    std::array<uint8_t, 1> program{
        0b00111010, // LD to A from HLMINUSI
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1);
    EXPECT_EQ(cpu.registers.HL(), kAddr - 1);
}

TEST_F(LDTest, LD_NNI_A) {
    std::array<uint8_t, 3> program{
        0b11101010, // LD (nn), A
        LSB(kBigAddr),
        MSB(kBigAddr),
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(kBigAddr), kVal1);
    EXPECT_EQ(cpu.registers.PC, 0x0003);
}

TEST_F(LDTest, LD_A_NNI) {
    std::array<uint8_t, 3> program{
        0b11111010, // LD A, (nn)
        LSB(kBigAddr),
        MSB(kBigAddr),
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.memory.Write8(kBigAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1);
    EXPECT_EQ(cpu.registers.PC, 0x0003);
}

TEST_F(LDTest, LDH_CI_A) {
    std::array<uint8_t, 1> program{
        0b11100010, // LDH (C), A
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.registers.C = kAddr;
    cpu.Step();
    EXPECT_EQ(memory.Read8(PromoteH(kAddr)), kVal1);
}

TEST_F(LDTest, LD_A_CI) {
    std::array<uint8_t, 1> program{
        0b11110010, // LD A, (CI)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.C = static_cast<uint8_t>(kAddr);
    cpu.memory.Write8(PromoteH(kAddr), kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1);
}

TEST_F(LDTest, LDH_NI_A) {
    std::array<uint8_t, 2> program{
        0b11100000, // LDH (n), A
        kAddr,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.A = kVal1;
    cpu.Step();
    EXPECT_EQ(memory.Read8(PromoteH(kAddr)), kVal1);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
}

TEST_F(LDTest, LD_A_NI) {
    std::array<uint8_t, 2> program{
        0b11110000, // LD A, (n)
        kAddr,
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.memory.Write8(PromoteH(kAddr), kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, kVal1);
    EXPECT_EQ(cpu.registers.PC, 0x0002);
}

TEST_F(LDTest, LD_BC_NN) {
    std::array<uint8_t, 3> program{
        0b00000001, // LD BC, nn
        LSB(kBigVal1),
        MSB(kBigVal1),
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.Step();
    EXPECT_EQ(cpu.registers.BC(), kBigVal1);
    EXPECT_EQ(cpu.registers.PC, 0x0003);
}

TEST_F(LDTest, LD_NNI_SP) {
    std::array<uint8_t, 3> program{
        0b00001000, // LD (nn), SP
        LSB(kBigAddr),
        MSB(kBigAddr),
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SP = kBigVal1;
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read16(kBigAddr), kBigVal1);
    EXPECT_EQ(cpu.registers.PC, 0x0003);
}
