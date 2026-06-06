#include "src/emulator/op/bit.h"

#include "src/emulator/util.h"

#include "absl/log/log.h"

void CP(Registers& registers, uint8_t val) {
    auto [res, borrow_per_bit] = OverflowingSub(registers.A, val);
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, true);
    registers.SetFlag(H_FLAG, borrow_per_bit[3]);
    registers.SetFlag(C_FLAG, borrow_per_bit[7]);
}

CP::CP(Target target) : target(target) {}

std::unique_ptr<Op> CP::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<CP>(target);
}

std::string CP::Print() const {
    return "CP, target: " + ::Print(target);
}

void CP::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetTarget(registers, memory, target);
    ::CP(registers, val);
}

std::unique_ptr<Op> CP_N::Decode(uint8_t op_code) {
    return std::make_unique<CP_N>();
}

std::string CP_N::Print() const {
    return "CP_N";
}

void CP_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetNext8(registers, memory);
    ::CP(registers, val);
}

void AND(Registers& registers, uint8_t val) {
    uint8_t res = registers.A & val;
    registers.A = res;
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, true);
    registers.SetFlag(C_FLAG, false);
}

AND::AND(Target target) : target(target) {}

std::unique_ptr<Op> AND::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<AND>(target);
}

std::string AND::Print() const {
    return "AND, target: " + ::Print(target);
}

void AND::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetTarget(registers, memory, target);
    ::AND(registers, val);
}

std::unique_ptr<Op> AND_N::Decode(uint8_t op_code) {
    return std::make_unique<AND_N>();
}

std::string AND_N::Print() const {
    return "AND_N";
}

void AND_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetNext8(registers, memory);
    ::AND(registers, val);
}

void OR(Registers& registers, uint8_t val) {
    uint8_t res = registers.A | val;
    registers.A = res;
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, false);
    registers.SetFlag(C_FLAG, false);
}

OR::OR(Target target) : target(target) {}

std::unique_ptr<Op> OR::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<OR>(target);
}

std::string OR::Print() const {
    return "OR, target: " + ::Print(target);
}

void OR::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetTarget(registers, memory, target);
    ::OR(registers, val);
}

std::unique_ptr<Op> OR_N::Decode(uint8_t op_code) {
    return std::make_unique<OR_N>();
}

std::string OR_N::Print() const {
    return "OR_N";
}

void OR_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetNext8(registers, memory);
    ::OR(registers, val);
}

void XOR(Registers& registers, uint8_t val) {
    uint8_t res = registers.A ^ val;
    registers.A = res;
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, false);
    registers.SetFlag(C_FLAG, false);
}

XOR::XOR(Target target) : target(target) {}

std::unique_ptr<Op> XOR::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<XOR>(target);
}

std::string XOR::Print() const {
    return "XOR, target: " + ::Print(target);
}

void XOR::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetTarget(registers, memory, target);
    ::XOR(registers, val);
}

std::unique_ptr<Op> XOR_N::Decode(uint8_t op_code) {
    return std::make_unique<XOR_N>();
}

std::string XOR_N::Print() const {
    return "XOR_N";
}

void XOR_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = GetNext8(registers, memory);
    ::XOR(registers, val);
}

std::unique_ptr<Op> CCF::Decode(uint8_t op_code) {
    return std::make_unique<CCF>();
}

std::string CCF::Print() const {
    return "CCF";
}

void CCF::ExecuteImpl(Registers& registers, Memory& memory) {
    registers.SetFlag(Flag::N_FLAG, false);
    registers.SetFlag(Flag::H_FLAG, false);
    registers.FlipFlag(Flag::C_FLAG);
}

std::unique_ptr<Op> SCF::Decode(uint8_t op_code) {
    return std::make_unique<SCF>();
}

std::string SCF::Print() const {
    return "SCF";
}

void SCF::ExecuteImpl(Registers& registers, Memory& memory) {
    registers.SetFlag(Flag::C_FLAG, true);
    registers.SetFlag(Flag::N_FLAG, false);
    registers.SetFlag(Flag::H_FLAG, false);
}

std::unique_ptr<Op> DAA::Decode(uint8_t op_code) {
    return std::make_unique<DAA>();
}

std::string DAA::Print() const {
    return "DAA";
}

void DAA::ExecuteImpl(Registers& registers, Memory& memory) {
    // referenced:
    // https://github.com/Gekkio/mooneye-gb/blob/754403792d60821e12835ba454d7e8b66553ed22/core/src/cpu/mod.rs#L812-L846
    // https://github.com/rylev/DMG-01/blob/00bed9baedab5548d63d646f60acb7af4b3e3658/lib-dmg-01/src/cpu/mod.rs#L1337
    bool carry = false;
    if (!registers.GetFlag(Flag::N_FLAG)) { // prev op was ADD/ADC
        if (registers.GetFlag(Flag::C_FLAG) || registers.A > 0x99) {
            registers.A += 0x60;
            carry = true;
        }
        if (registers.GetFlag(Flag::H_FLAG) || LowerNibble(registers.A) > 0x09) {
            registers.A += 0x06;
        }
    } else if (registers.GetFlag(Flag::C_FLAG)) {
        carry = true;
        registers.A += registers.GetFlag(Flag::H_FLAG) ? 0x9A : 0xA0;
    } else if (registers.GetFlag(Flag::H_FLAG)) {
        registers.A += 0xFA;
    }

    registers.SetFlag(Flag::Z_FLAG, registers.A == 0);
    registers.SetFlag(Flag::H_FLAG, false);
    registers.SetFlag(Flag::C_FLAG, carry);
}

std::unique_ptr<Op> CPL::Decode(uint8_t op_code) {
    return std::make_unique<CPL>();
}

std::string CPL::Print() const {
    return "CPL";
}

void CPL::ExecuteImpl(Registers& registers, Memory& memory) {
    registers.A = ~registers.A;
    registers.SetFlag(Flag::N_FLAG, true);
    registers.SetFlag(Flag::H_FLAG, true);
}
