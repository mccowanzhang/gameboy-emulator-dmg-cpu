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
    uint8_t op_code = Fetch8();
    auto op = DecodeOp(op_code);
    op->Execute(registers, memory);
}

uint8_t CPU::Fetch8() {
    LOG(INFO) << "Fetch 8 bits from " << std::hex << registers.PC;
    uint8_t val = memory.Read8(registers.PC);
    LOG(INFO) << "Fetched 8 bytes: " << std::bitset<8>(val);
    registers.PC += 1;
    return val;
}

uint16_t CPU::Fetch16() {
    uint8_t val = memory.Read16(registers.PC);
    registers.PC += 2;
    return val;
}