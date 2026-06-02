#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

class LDTest : public ::testing::Test {
protected:
    static constexpr uint8_t kVal1 = 3;
    static constexpr uint8_t kVal2 = 5;
    static constexpr uint16_t kAddr = 0x0040;
    static constexpr uint16_t kStartPC = 0x0000;

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
