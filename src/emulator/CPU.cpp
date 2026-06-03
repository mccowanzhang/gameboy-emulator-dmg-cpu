#include "src/emulator/CPU.h"

#include "src/emulator/memory.h"
#include "src/emulator/op/decoder.h"

#include "absl/log/log.h"

#include <iomanip>
#include <bitset>

CPU::CPU(Memory& memory) : memory(memory) {
    Reset();
}

void CPU::Reset() {
    memory.Reset();
    registers = {};
}

void CPU::Step() {
    uint8_t op_code = GetNext8(registers, memory);
    auto op = DecodeOp(op_code);
    op->Execute(registers, memory);
}
