#include "src/emulator/op.h"

#include <gtest/gtest.h>
#include <iostream>
#include <memory>

TEST(Op, NOP) {
    auto nop = NOP();

    std::stringstream ss;
    nop.Print(ss);
    EXPECT_EQ(ss.str(), "NOP\n");

    std::unique_ptr<Op> op = std::make_unique<NOP>(); 
    ss.str("");
    ss.clear();
    ss << *op;
    EXPECT_EQ(ss.str(), "NOP\n");
}