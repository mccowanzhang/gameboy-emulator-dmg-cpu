#pragma once 

#include "src/emulator/op/add.h"
#include "src/emulator/op/ld.h"
#include "src/emulator/op/nop.h"
#include "src/emulator/op/stack.h"
#include "src/emulator/op/sub.h"

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
        .value = 0b00001000,
        .mask =  0b11111111,
        .decoder = &LD_NNI_SP::Decode,
    },
    {
        .value = 0b11111001,
        .mask =  0b11111111,
        .decoder = &LD_SP_HL::Decode,
    },
    {
        .value = 0b11111000,
        .mask =  0b11111111,
        .decoder = &LD_HL_SPE::Decode,
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
        .value = 0b11000101,
        .mask =  0b11001111,
        .decoder = &PUSH::Decode,
    },
    {
        .value = 0b11000001,
        .mask =  0b11001111,
        .decoder = &POP::Decode,
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
        .value = 0b11000110,
        .mask =  0b11111111,
        .decoder = &ADD_N::Decode,
    },
    {
        .value = 0b10001000,
        .mask =  0b11111000,
        .decoder = &ADC::Decode,
    },
    {
        .value = 0b11001110,
        .mask =  0b11111111,
        .decoder = &ADC_N::Decode,
    },
    {
        .value = 0b10010000,
        .mask =  0b11111000,
        .decoder = &SUB::Decode,
    },
    {
        .value = 0b11010110,
        .mask =  0b11111111,
        .decoder = &SUB_N::Decode,
    },
    {
        .value = 0b10011000,
        .mask =  0b11111000,
        .decoder = &SBC::Decode,
    },
};

std::unique_ptr<Op> DecodeOp(uint8_t op_code);