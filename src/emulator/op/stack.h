#pragma once 

#include "src/emulator/op/op_base.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"

enum class Stack_Target : uint8_t {
    BC = 0b00,
    DE = 0b01,
    HL = 0b10,
    AF = 0b11,
};
std::string Print(Stack_Target target);
class PUSH : public Op {
public:
    explicit PUSH(Stack_Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Stack_Target target;
};
