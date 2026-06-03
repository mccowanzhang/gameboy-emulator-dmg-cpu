#pragma once 

#include "src/emulator/op/ld.h"
#include "src/emulator/op/add.h"
#include "src/emulator/op/nop.h"

#include <memory>
#include <vector>

struct DecodeRule {
    uint8_t value;
    uint8_t mask;
    std::unique_ptr<Op>(*decoder)(uint8_t);
};

static const std::vector<DecodeRule> kDecodeRules = {
    {
        .value = 0b01000000,
        .mask =  0b11000000,
        .decoder = &LD::Decode,
    },
    {
        .value = 0b00000110,
        .mask =  0b11000111,
        .decoder = &LD_R_N::Decode,
    },
    {
        .value = 0b00000010,
        .mask =  0b11000111,
        .decoder = &LD_RR::Decode,
    },
    {
        .value = 0b00000001,
        .mask =  0b11001111,
        .decoder = &LD_RR_NN::Decode,
    },
    {
        .value = 0b11101010,
        .mask =  0b11101111,
        .decoder = &LD_NNI::Decode,
    },
    {
        .value = 0b11100010,
        .mask =  0b11101111,
        .decoder = &LDH_C::Decode,
    },
    {
        .value = 0b11100000,
        .mask =  0b11101111,
        .decoder = &LDH_NI::Decode,
    },
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