#include "src/emulator/registers.h"

#include <gtest/gtest.h>

TEST(Registers, Flags) {
    auto registers = Registers();

    EXPECT_EQ(registers.GetFlag(Flag::Z_FLAG), false);
    EXPECT_EQ(registers.GetFlag(Flag::N_FLAG), false);
    EXPECT_EQ(registers.GetFlag(Flag::H_FLAG), false);
    EXPECT_EQ(registers.GetFlag(Flag::C_FLAG), false);

    registers.SetF(0xFF);

    EXPECT_EQ(registers.GetFlag(Flag::Z_FLAG), true);
    EXPECT_EQ(registers.GetFlag(Flag::N_FLAG), true);
    EXPECT_EQ(registers.GetFlag(Flag::H_FLAG), true);
    EXPECT_EQ(registers.GetFlag(Flag::C_FLAG), true);

    registers.SetFlag(Flag::Z_FLAG, false);
    EXPECT_EQ(registers.GetFlag(Flag::Z_FLAG), false);
    registers.SetFlag(Flag::Z_FLAG, true);
    EXPECT_EQ(registers.GetFlag(Flag::Z_FLAG), true);

    registers.SetFlag(Flag::N_FLAG, false);
    EXPECT_EQ(registers.GetFlag(Flag::N_FLAG), false);
    registers.SetFlag(Flag::N_FLAG, true);
    EXPECT_EQ(registers.GetFlag(Flag::N_FLAG), true);

    registers.SetFlag(Flag::H_FLAG, false);
    EXPECT_EQ(registers.GetFlag(Flag::H_FLAG), false);
    registers.SetFlag(Flag::H_FLAG, true);
    EXPECT_EQ(registers.GetFlag(Flag::H_FLAG), true);

    registers.SetFlag(Flag::C_FLAG, false);
    EXPECT_EQ(registers.GetFlag(Flag::C_FLAG), false);
    registers.SetFlag(Flag::C_FLAG, true);
    EXPECT_EQ(registers.GetFlag(Flag::C_FLAG), true);
}

TEST(Registers, CombinedHalfRegisters) {
    auto registers = Registers();

    EXPECT_EQ(registers.AF(), 0x0000);
    registers.A = 0x12;
    registers.SetF(0x34);
    EXPECT_EQ(registers.AF(), 0x1230);
    registers.SetAF(0x5678);
    EXPECT_EQ(registers.AF(), 0x5670);

    EXPECT_EQ(registers.BC(), 0x0000);
    registers.B = 0x12;
    registers.C = 0x34;
    EXPECT_EQ(registers.BC(), 0x1234);
    registers.SetBC(0x5678);
    EXPECT_EQ(registers.BC(), 0x5678);

    EXPECT_EQ(registers.DE(), 0x0000);
    registers.D = 0x12;
    registers.E = 0x34;
    EXPECT_EQ(registers.DE(), 0x1234);
    registers.SetDE(0x5678);
    EXPECT_EQ(registers.DE(), 0x5678);

    EXPECT_EQ(registers.HL(), 0x0000);
    registers.H = 0x12;
    registers.L = 0x34;
    EXPECT_EQ(registers.HL(), 0x1234);
    registers.SetHL(0x5678);
    EXPECT_EQ(registers.HL(), 0x5678);
}

TEST(Registers, Comparison) {
    auto registers1 = Registers();
    auto registers2 = Registers();
    EXPECT_EQ(registers1, registers2);
    registers2.A += 1;
    EXPECT_NE(registers1, registers2);

    registers2 = Registers();
    registers2.B += 1;
    EXPECT_NE(registers1, registers2);

    registers2 = Registers();
    registers2.C += 1;
    EXPECT_NE(registers1, registers2);

    registers2 = Registers();
    registers2.D += 1;
    EXPECT_NE(registers1, registers2);
    
    registers2 = Registers();
    registers2.E += 1;
    EXPECT_NE(registers1, registers2);

    registers2 = Registers();
    registers2.SetFlag(Flag::Z_FLAG, true);
    EXPECT_NE(registers1, registers2);

    registers2 = Registers();
    registers2.H += 1;
    EXPECT_NE(registers1, registers2);

    registers2 = Registers();
    registers2.L += 1;
    EXPECT_NE(registers1, registers2);
}