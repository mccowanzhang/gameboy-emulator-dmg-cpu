#pragma once 

#include "src/emulator/op/op_base.h"

#include <memory>

std::unique_ptr<Op> ParseOp(uint8_t op_code);