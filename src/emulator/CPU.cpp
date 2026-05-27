#include "src/emulator/CPU.h"

#include "src/emulator/memory.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

CPU::CPU(Memory& memory) : memory_(memory) {
    Reset();
}

void CPU::Reset() {
    memory_.Reset();
    registers_ = {};
}

Registers CPU::GetRegisters() {
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

void CPU::ADD(ArithTarget target) {
    uint8_t val = 0;
    switch (target) {
        case A:
            val = registers_.A;
            break;
        case B:
            val = registers_.B;
            break;
        case C:
            val = registers_.C;
            break;
        case D:
            val = registers_.D;
            break;
        case E:
            val = registers_.E;
            break;
        case H:
            val = registers_.H;
            break;
        case L:
            val = registers_.L;
            break;
        default:
            LOG(FATAL) << "Unrecognized ADD target\n";
    }

    uint8_t new_val;
    bool overflowed = OverflowingAdd<uint8_t>(registers_.A, val, new_val);
    registers_.SetFlag(Z_FLAG, new_val == 0);
    registers_.SetFlag(N_FLAG, false);
    registers_.SetFlag(H_FLAG, (registers_.A & 0x0F) + (new_val & 0x0F) > 0x0F);
    registers_.SetFlag(C_FLAG, overflowed);
    registers_.A = new_val;
}