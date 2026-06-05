#include "src/emulator/op/op_base.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"

#include "absl/log/log.h"

#include <bitset>
#include <iostream>

void Op::Execute(Registers& registers, Memory& memory) {
    LOG(INFO) << "Executing: " << Print();
    ExecuteImpl(registers, memory);
}

std::string Print(Target target) {
    switch (target) {
        case Target::A:
            return "A";
        case Target::B:
            return "B";
        case Target::C:
            return "C";
        case Target::D:
            return "D";
        case Target::E:
            return "E";
        case Target::H:
            return "H";
        case Target::L:
            return "L";
        case Target::HLI:
            return "HLI";
        default:
            return "Unrecognized target";
    }
}

std::string Print(RR_Target target) {
    switch (target) {
        case RR_Target::BC:
            return "BC";
        case RR_Target::DE:
            return "DE";
        case RR_Target::HL:
            return "HL";
        case RR_Target::SP:
            return "SP";
        default:
            return "Unrecognized LD RR NN target";
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
