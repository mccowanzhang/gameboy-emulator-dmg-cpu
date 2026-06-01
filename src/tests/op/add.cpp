#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

#include <iostream>
#include <limits>
#include <memory>

TEST(ADD, Print) {
    auto add = ADD(ArithTarget::A);

    std::string expected("ADD, target: A");
    EXPECT_EQ(add.Print(), expected);

    std::stringstream ss;
    add.Op::Print(ss);
    EXPECT_EQ(ss.str(), expected);

    std::unique_ptr<Op> op = std::make_unique<ADD>(ArithTarget::A); 
    ss.str("");
    ss.clear();
    ss << *op;
    EXPECT_EQ(ss.str(), expected);

    ss.str("");
    ss.clear();
    op->Print(ss);
    EXPECT_EQ(ss.str(), expected);
}

TEST(ADD, ADD) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    cpu.memory.Write8(0x0000, 0b10000000); // add B to A
    cpu.registers.A = 3;
    cpu.registers.B = 5;
    cpu.Step();
    EXPECT_EQ(cpu.registers.A, 8);
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::Z_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::N_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::H_FLAG));
    EXPECT_FALSE(cpu.registers.GetFlag(Flag::C_FLAG));
    // TODO: TEST HLI
}

TEST(ADD, ADC) {
    auto memory = Memory();
    auto cpu = CPU(memory);
    std::array<uint8_t, 2> program{
        0b10000000, // ADD B to A
        0b10001001, // ADC C to A
    };
    cpu.memory.WriteProgram(0x0000, program);
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