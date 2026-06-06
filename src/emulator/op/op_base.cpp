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

uint8_t GetTarget(Registers& registers, Memory& memory, Target target) {
    switch (target) {
        case Target::A:
            return registers.A;
        case Target::B:
            return registers.B;
        case Target::C:
            return registers.C;
        case Target::D:
            return registers.D;
        case Target::E:
            return registers.E;
        case Target::H:
            return registers.H;
        case Target::L:
            return registers.L;
        case Target::HLI:
            return memory.Read8(registers.HL());
        default:
            LOG(FATAL) << "Unrecognized target";
            return 0;
    }
}

void SetTarget(Registers& registers, Memory& memory, Target target, uint8_t val) {
    switch (target) {
        case Target::A:
            registers.A = val;
            break;
        case Target::B:
            registers.B = val;
            break;
        case Target::C:
            registers.C = val;
            break;
        case Target::D:
            registers.D = val;
            break;
        case Target::E:
            registers.E = val;
            break;
        case Target::H:
            registers.H = val;
            break;
        case Target::L:
            registers.L = val;
            break;
        case Target::HLI:
            memory.Write8(registers.HL(), val);
            break;
        default:
            LOG(FATAL) << "Unrecognized target";
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

uint16_t GetRRTarget(Registers& registers, RR_Target target) {
    switch (target) {
        case RR_Target::BC:
            return registers.BC();
        case RR_Target::DE:
            return registers.DE();
        case RR_Target::HL:
            return registers.HL();
        case RR_Target::SP:
            return registers.SP;
        default:
            LOG(FATAL) << "Unrecognized RR target";
            return 0;
    }
}

void SetRRTarget(Registers& registers, RR_Target target, uint16_t val) {
    switch (target) {
        case RR_Target::BC:
            registers.SetBC(val);
            break;
        case RR_Target::DE:
            registers.SetDE(val);
            break;
        case RR_Target::HL:
            registers.SetHL(val);
            break;
        case RR_Target::SP:
            registers.SP = val;
            break;
        default:
            LOG(FATAL) << "Unrecognized RR target";
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
