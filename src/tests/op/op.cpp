#include "src/emulator/op/op.h"
#include "src/emulator/op/nop.h"

#include <gtest/gtest.h>
#include <iostream>
#include <memory>

TEST(Op, NOP) {
    EXPECT_EQ(1 + 1, 2);
}