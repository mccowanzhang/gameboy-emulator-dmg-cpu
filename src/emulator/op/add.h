#pragma once

#include "src/emulator/op/op_base.h"

#include <memory>

enum ArithTarget : uint8_t {
    A, B, C, D, E, H, L,
};

class ADD : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t opcode);
    void Execute(Memory& memory, Registers& registers) override;
    std::string Print() const override;
private:
    ArithTarget target;
};