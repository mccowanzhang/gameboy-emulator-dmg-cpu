#pragma once

#include "src/emulator/op/op_base.h"

enum ArithTarget : uint8_t {
    A, B, C, D, E, H, L,
};

class ADD : public Op {
public:
    void Execute(Memory& memory, Registers& registers) override;
    std::string Print() const override;
private:
    ArithTarget target;
};