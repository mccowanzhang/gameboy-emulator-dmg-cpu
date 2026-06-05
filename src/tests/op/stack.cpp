#include "src/emulator/op/stack.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

#include <limits>
#include <memory>

class STACKTest : public ::testing::Test {
protected:
    static constexpr uint16_t kBigVal1 = 0x1234;
    static constexpr uint16_t kAddr = 0x0040;
    static constexpr uint16_t kStartPC = 0x0000;

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
