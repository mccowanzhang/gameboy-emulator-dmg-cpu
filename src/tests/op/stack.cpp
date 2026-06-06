#include "src/emulator/op/stack.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"
#include "src/tests/test_base.h"

#include <gtest/gtest.h>

#include <limits>
#include <memory>

class STACKTest : public ::testing::Test {
protected:
    Memory memory;
    CPU cpu{memory};
};

TEST_F(STACKTest, PUSH) {
    std::array<uint8_t, 1> program{
        0b11000101, // PUSH BC
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SetBC(kBigVal1);
    cpu.registers.SP = kAddr;
    cpu.Step();
    EXPECT_EQ(cpu.registers.SP, kAddr - 2);
    EXPECT_EQ(cpu.memory.Read16(kAddr - 2), kBigVal1);
}

TEST_F(STACKTest, POP) {
    std::array<uint8_t, 1> program{
        0b11000001, // POP BC
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.memory.Write16(kAddr, kBigVal1);
    cpu.registers.SP = kAddr;
    cpu.Step();
    EXPECT_EQ(cpu.registers.SP, kAddr + 2);
    EXPECT_EQ(cpu.registers.BC(), kBigVal1);
}

TEST_F(STACKTest, PUSH_POP) {
    std::array<uint8_t, 2> program{
        0b11000101, // PUSH BC
        0b11010001, // POP DE
    };
    cpu.memory.WriteProgram(kStartPC, program);
    cpu.registers.SP = kAddr;
    cpu.registers.SetBC(kBigVal1);
    cpu.Step();
    cpu.Step();
    EXPECT_EQ(cpu.registers.SP, kAddr);
    EXPECT_EQ(cpu.registers.DE(), kBigVal1);
}
