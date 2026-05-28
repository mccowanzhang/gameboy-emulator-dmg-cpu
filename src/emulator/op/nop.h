#pragma once

#include "src/emulator/op/op_base.h"

class NOP : public Op {
public:
    void Execute(Memory& memory, Registers& registers) override;
    std::string Print() const override;
    static constexpr uint8_t kOpCode = 0x00;
};