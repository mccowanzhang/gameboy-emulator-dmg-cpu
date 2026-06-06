#include "src/emulator/op/stack.h"

#include "absl/log/log.h"

std::string Print(Stack_Target target) {
    switch (target) {
        case Stack_Target::BC:
            return "BC";
        case Stack_Target::DE:
            return "DE";
        case Stack_Target::HL:
            return "HL";
        case Stack_Target::AF:
            return "AF";
        default:
            return "Unrecognized stack target";
    }
}

uint16_t GetStackTarget(Registers& registers, Stack_Target target) {
    switch (target) {
        case Stack_Target::BC:
            return registers.BC();
        case Stack_Target::DE:
            return registers.DE();
        case Stack_Target::HL:
            return registers.HL();
        case Stack_Target::AF:
            return registers.AF();
        default:
            LOG(FATAL) << "Unrecognized stack target";
            return 0;
    }
}

void SetStackTarget(Registers& registers, Stack_Target target, uint16_t val) {
    switch (target) {
        case Stack_Target::BC:
            registers.SetBC(val);
            break;
        case Stack_Target::DE:
            registers.SetDE(val);
            break;
        case Stack_Target::HL:
            registers.SetHL(val);
            break;
        case Stack_Target::AF:
            registers.SetAF(val);
            break;
        default:
            LOG(FATAL) << "Unrecognized stack target";
    }
}

PUSH::PUSH(Stack_Target target) : target(target) {}

std::unique_ptr<Op> PUSH::Decode(uint8_t op_code) {
    auto target = static_cast<Stack_Target>(GetBitRange(op_code, 4, 5));
    return std::make_unique<PUSH>(target);
}

std::string PUSH::Print() const {
    return "PUSH, target: " + ::Print(target);
}

void PUSH::ExecuteImpl(Registers& registers, Memory& memory) {
    registers.SP = registers.SP - 2;
    memory.Write16(registers.SP, GetStackTarget(registers, target));
}

POP::POP(Stack_Target target) : target(target) {}

std::unique_ptr<Op> POP::Decode(uint8_t op_code) {
    auto target = static_cast<Stack_Target>(GetBitRange(op_code, 4, 5));
    return std::make_unique<POP>(target);
}

std::string POP::Print() const {
    return "POP, target: " + ::Print(target);
}

void POP::ExecuteImpl(Registers& registers, Memory& memory) {
    uint16_t val = memory.Read16(registers.SP);
    SetStackTarget(registers, target, val);
    registers.SP = registers.SP + 2;
}
