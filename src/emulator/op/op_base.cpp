#include "src/emulator/op/op_base.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"

#include "absl/log/log.h"

#include <bitset>
#include <iostream>

void Op::Execute(Registers& registers, Memory& memory) {
    LOG(INFO) << "Executing " << Print();
    ExecuteImpl(registers, memory);
}

std::string Print(Target target) {
    switch (target) {
        case A:
            return "A";
        case B:
            return "B";
        case C:
            return "C";
        case D:
            return "D";
        case E:
            return "E";
        case H:
            return "H";
        case L:
            return "L";
        case HLI:
            return "HLI";
        default:
            return "Unrecognized target";
    }
}

uint8_t GetNext8(Registers& registers, Memory& memory) {
    uint8_t val = memory.Read8(registers.PC);
    registers.PC += 1;
    return val;
}

uint16_t GetNext16(Registers& registers, Memory& memory) {
    uint8_t val = memory.Read16(registers.PC);
    registers.PC += 2;
    return val;
}
