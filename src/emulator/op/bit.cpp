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
