#pragma once 

#include "src/emulator/op/op_base.h"

#include <memory>
#include <vector>

std::unique_ptr<Op> DecodeNOP(uint8_t op_code);
std::unique_ptr<Op> DecodeADD(uint8_t op_code);

struct DecodeRule {
    uint8_t value;
    uint8_t mask;
    std::unique_ptr<Op>(*decoder)(uint8_t) ;
};

static const std::vector<DecodeRule> kDecodeRules = {
    {
        .value = 0x00,
        .mask = 0xFF,
        .decoder = DecodeNOP,
    },
};

std::unique_ptr<Op> DecodeOp(uint8_t op_code);