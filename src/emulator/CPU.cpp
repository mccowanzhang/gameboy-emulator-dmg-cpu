#include "src/emulator/CPU.h"

#include "src/emulator/memory.h"

CPU::CPU(Memory& memory) : memory_(memory) {
    Reset();
}

void CPU::Reset() {
    memory_.Reset();
    registers_ = {};
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