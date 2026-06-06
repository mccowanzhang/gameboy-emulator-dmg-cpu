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
