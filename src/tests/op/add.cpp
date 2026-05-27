#include "src/emulator/op/add.h"

#include <gtest/gtest.h>
#include <iostream>
#include <memory>

TEST(Op, Print) {
    auto add = ADD();

    std::string expected("ADD");
    EXPECT_EQ(add.Print(), expected);

    std::stringstream ss;
    add.Op::Print(ss);
    EXPECT_EQ(ss.str(), expected);

    std::unique_ptr<Op> op = std::make_unique<ADD>(); 
    ss.str("");
    ss.clear();
    ss << *op;
    EXPECT_EQ(ss.str(), expected);

    ss.str("");
    ss.clear();
    op->Print(ss);
    EXPECT_EQ(ss.str(), expected);
}