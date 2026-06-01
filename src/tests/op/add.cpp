#include "src/emulator/op/add.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>

#include <iostream>
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
}