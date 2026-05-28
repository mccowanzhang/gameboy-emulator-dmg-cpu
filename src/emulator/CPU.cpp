#include "src/emulator/CPU.h"

#include "src/emulator/memory.h"
#include "src/emulator/op/op.h"

CPU::CPU(Memory& memory) : memory_(memory) {
    Reset();
}

void CPU::Reset() {
    memory_.Reset();
    registers_ = {};
}

void CPU::Step() {
    uint8_t op_code = Fetch8();
    auto op = ParseOp(op_code);
    op->Execute(memory_, registers_);
}

Registers CPU::GetRegisters() const {
    return registers_;
}

uint8_t CPU::Fetch8() {
    uint8_t val = memory_.Read8(registers_.PC);
    registers_.PC += 1;
    return val;
}

uint16_t CPU::Fetch16() {
    uint8_t val = memory_.Read16(registers_.PC);
    registers_.PC += 2;
    return val;
}