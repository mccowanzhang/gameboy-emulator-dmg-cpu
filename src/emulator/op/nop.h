#pragma once

#include "src/emulator/op/op_base.h"

class NOP : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t opcode);
    void Execute(Registers& registers, Memory& memory) override;
    std::string Print() const override;
    static constexpr uint8_t kOpCode = 0x00;
};