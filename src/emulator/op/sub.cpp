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

void SBC(Registers& registers, uint8_t val) {
    auto [res1, carry_per_bit1] = OverflowingAdd<uint8_t>(
        val,
        static_cast<uint8_t>(registers.GetFlag(Flag::C_FLAG))
    );
    SUB(registers, res1);
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

SBC::SBC(Target target) : target(target) {}

std::unique_ptr<Op> SBC::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<SBC>(target);
}

std::string SBC::Print() const {
    return "SBC, target: " + ::Print(target);
}

void SBC::ExecuteImpl(Registers& registers, Memory& memory) {
    switch (target) {
        case Target::A:
            ::SBC(registers, registers.A);
            break;
        case Target::B:
            ::SBC(registers, registers.B);
            break;
        case Target::C:
            ::SBC(registers, registers.C);
            break;
        case Target::D:
            ::SBC(registers, registers.D);
            break;
        case Target::E:
            ::SBC(registers, registers.E);
            break;
        case Target::H:
            ::SBC(registers, registers.H);
            break;
        case Target::L:
            ::SBC(registers, registers.L);
            break;
        case Target::HLI:
            ::SBC(registers, memory.Read8(registers.HL()));
            break;
        default:
            LOG(FATAL) << "Unrecognized SBC target";
    }
}