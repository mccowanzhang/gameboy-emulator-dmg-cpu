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