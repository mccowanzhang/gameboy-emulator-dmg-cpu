#include "src/emulator/op/nop.h"

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