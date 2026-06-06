#include "src/emulator/op/inc.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/tests/test_base.h"

#include "gtest/gtest.h"

class INCTest : public ::testing::Test {
protected:
    Memory memory;
    CPU cpu{memory};
};

TEST_F(INCTest, INC) {
    std::array<uint8_t, 1> program{
        0b00000100, // INC B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.B = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.B, kVal1 + 1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
}

TEST_F(INCTest, INC_HLI) {
    std::array<uint8_t, 1> program{
        0b00110100, // INC (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal1 + 1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
}

TEST_F(INCTest, DEC) {
    std::array<uint8_t, 1> program{
        0b00000101, // DEC B
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.B = kVal1;
    cpu.Step();
    EXPECT_EQ(cpu.registers.B, kVal1 - 1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
}

TEST_F(INCTest, DEC_HLI) {
    std::array<uint8_t, 1> program{
        0b00110101, // DEC (HL)
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetHL(kAddr);
    cpu.memory.Write8(kAddr, kVal1);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(kAddr), kVal1 - 1);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_TRUE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
}
