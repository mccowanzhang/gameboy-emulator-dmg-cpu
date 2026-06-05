#include "src/emulator/op/stack.h"

#include "absl/log/log.h"

PUSH::PUSH(RR_Target target) : target(target) {}

std::unique_ptr<Op> PUSH::Decode(uint8_t op_code) {
    auto target = static_cast<RR_Target>(GetBitRange(op_code, 4, 5));
    return std::make_unique<PUSH>(target);
}

std::string PUSH::Print() const {
    return "PUSH, target: " + ::Print(target);
}

void PUSH::ExecuteImpl(Registers& registers, Memory& memory) {
    registers.SP = registers.SP - 2;
    switch (target) {
        case BC:
            memory.Write16(registers.SP, registers.BC());
        case DE:
            memory.Write16(registers.SP, registers.DE());
        case HL:
            memory.Write16(registers.SP, registers.HL());
        case SP:
            memory.Write16(registers.SP, registers.SP);
        default:
            LOG(FATAL) << "Unrecognized target";
    }
}
