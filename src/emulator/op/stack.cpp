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
    switch (target) {
        case Stack_Target::BC:
            memory.Write16(registers.SP, registers.BC());
            break;
        case Stack_Target::DE:
            memory.Write16(registers.SP, registers.DE());
            break;
        case Stack_Target::HL:
            memory.Write16(registers.SP, registers.HL());
            break;
        case Stack_Target::AF:
            memory.Write16(registers.SP, registers.AF());
            break;
        default:
            LOG(FATAL) << "Unrecognized target";
    }
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
    switch (target) {
        case Stack_Target::BC:
            registers.SetBC(memory.Read16(registers.SP));
            break;
        case Stack_Target::DE:
            registers.SetDE(memory.Read16(registers.SP));
            break;
        case Stack_Target::HL:
            registers.SetHL(memory.Read16(registers.SP));
            break;
        case Stack_Target::AF:
            registers.SetAF(memory.Read16(registers.SP));
            break;
        default:
            LOG(FATAL) << "Unrecognized target";
    }
    registers.SP = registers.SP + 2;
}
