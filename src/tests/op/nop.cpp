#include "src/emulator/op/nop.h"

#include "src/emulator/CPU.h"
#include "src/emulator/memory.h"

#include <gtest/gtest.h>
#include <iostream>
#include <memory>

TEST(Op, Print) {
    auto nop = NOP();

    std::string expected("NOP");
    EXPECT_EQ(nop.Print(), expected);

    std::stringstream ss;
    nop.Op::Print(ss);
    EXPECT_EQ(ss.str(), expected);

    std::unique_ptr<Op> op = std::make_unique<NOP>(); 
    ss.str("");
    ss.clear();
    ss << *op;
    EXPECT_EQ(ss.str(), expected);

    ss.str("");
    ss.clear();
    op->Print(ss);
    EXPECT_EQ(ss.str(), expected);
}

TEST(Op, NOP) {
    auto memory = Memory();
    memory.Write8(0x0000, 0x00);
    auto cpu = CPU(memory);
    auto prestep_registers = cpu.GetRegisters();
    cpu.Step();
    auto poststep_registers = cpu.GetRegisters();
    EXPECT_NE(prestep_registers, poststep_registers);
    EXPECT_EQ(poststep_registers.PC, 0x0001);
    poststep_registers.PC = prestep_registers.PC;
    EXPECT_EQ(prestep_registers, poststep_registers);
}