#include "src/emulator/op/decoder.h"
#include "src/emulator/op/nop.h"

#include <gtest/gtest.h>
#include <iostream>
#include <memory>

TEST(Decoder, NOP) {
    EXPECT_EQ(1 + 1, 2);
}