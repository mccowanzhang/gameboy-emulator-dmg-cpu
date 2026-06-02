#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

TEST(LD, LD_R_R) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    std::array<uint8_t, 1> program{
        0b01000001 // LD B, C
    };
    cpu.memory.WriteProgram(0x0000, program);
    cpu.registers.B = 3;
    cpu.registers.C = 5;
    cpu.Step();
    EXPECT_EQ(cpu.registers.B, cpu.registers.C);
    EXPECT_EQ(cpu.registers.B, 5);
}

TEST(LD, LD_HLI_R) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    std::array<uint8_t, 1> program{
        0b01110011 // LD to HLI from E
    };
    cpu.memory.WriteProgram(0x0000, program);
    uint8_t val = 5;
    cpu.registers.E = val;
    uint16_t addr = 0x0040;
    cpu.registers.SetHL(addr);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(addr), val);
}

TEST(LD, LD_R_HLI) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    std::array<uint8_t, 1> program{
        0b01010110 // LD to D from HLI
    };
    cpu.memory.WriteProgram(0x0000, program);
    cpu.registers.D = 3;
    uint8_t val = 5;
    uint16_t addr = 0x0040;
    memory.Write8(addr, val);
    cpu.registers.SetHL(addr);
    cpu.Step();
    EXPECT_EQ(cpu.registers.D, val);
}

TEST(LD, LD_R_N) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    uint8_t val = 5;
    std::array<uint8_t, 2> program{
        0b00000110, // LD to B from N
        val,
    };
    cpu.memory.WriteProgram(0x0000, program);
    cpu.Step();
    EXPECT_EQ(cpu.registers.B, val);
}

TEST(LD, LD_HLI_N) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    uint8_t val = 5;
    std::array<uint8_t, 2> program{
        0b000110110, // LD to HLI from N
        val,
    };
    cpu.memory.WriteProgram(0x0000, program);
    uint16_t addr = 0x0040;
    cpu.registers.SetHL(addr);
    cpu.Step();
    EXPECT_EQ(cpu.memory.Read8(addr), val);
}
