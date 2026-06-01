#pragma once 

#include "src/emulator/op/add.h"
#include "src/emulator/op/nop.h"

#include <memory>
#include <vector>

struct DecodeRule {
    uint8_t value;
    uint8_t mask;
    std::unique_ptr<Op>(*decoder)(uint8_t) ;
};

static const std::vector<DecodeRule> kDecodeRules = {
    {
        .value = 0b00000000,
        .mask =  0b11111111,
        .decoder = &NOP::Decode,
    },
    {
        .value = 0b10000000,
        .mask =  0b11111000,
        .decoder = &ADD::Decode,
    },
    {
        .value = 0b10001000,
        .mask =  0b11111000,
        .decoder = &ADC::Decode,
    },
};

std::unique_ptr<Op> DecodeOp(uint8_t op_code);