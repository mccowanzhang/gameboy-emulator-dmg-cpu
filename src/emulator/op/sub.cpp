#include "src/emulator/op/sub.h"

#include "src/emulator/util.h"

#include "absl/log/log.h"

void SUB(Registers& registers, uint8_t val) {
    auto [res, borrow_per_bit] = OverflowingSub(registers.A, val);
    registers.A = res;
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, true);
    registers.SetFlag(H_FLAG, borrow_per_bit[3]);
    registers.SetFlag(C_FLAG, borrow_per_bit[7]);
}

SUB::SUB(Target target) : target(target) {}

std::unique_ptr<Op> SUB::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<SUB>(target);
}

std::string SUB::Print() const {
    return "SUB, target: " + ::Print(target);
}

void SUB::ExecuteImpl(Registers& registers, Memory& memory) {
    switch (target) {
        case Target::A:
            ::SUB(registers, registers.A);
            break;
        case Target::B:
            ::SUB(registers, registers.B);
            break;
        case Target::C:
            ::SUB(registers, registers.C);
            break;
        case Target::D:
            ::SUB(registers, registers.D);
            break;
        case Target::E:
            ::SUB(registers, registers.E);
            break;
        case Target::H:
            ::SUB(registers, registers.H);
            break;
        case Target::L:
            ::SUB(registers, registers.L);
            break;
        case Target::HLI:
            ::SUB(registers, memory.Read8(registers.HL()));
            break;
        default:
            LOG(FATAL) << "Unrecognized SUB target";
    }
}

std::unique_ptr<Op> SUB_N::Decode(uint8_t op_code) {
    return std::make_unique<SUB_N>();
}

std::string SUB_N::Print() const {
    return "SUB_N";
}

void SUB_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t n = GetNext8(registers, memory);
    ::SUB(registers, n);
}

