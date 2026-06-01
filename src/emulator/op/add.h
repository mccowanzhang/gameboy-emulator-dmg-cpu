#pragma once

#include "src/emulator/op/op_base.h"

#include <memory>

enum ArithTarget : uint8_t {
    A = 0b111,
    B = 0b000,
    C = 0b001,
    D = 0b010,
    E = 0b011,
    H = 0b100,
    L = 0b101,
    HLI = 0b110,
    // n
};
std::string Print(ArithTarget target);

class ADD : public Op {
public:
    explicit ADD(ArithTarget target);
    static std::unique_ptr<Op> Decode(uint8_t opcode);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    ArithTarget target;
};