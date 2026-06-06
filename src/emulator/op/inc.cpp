#include "src/emulator/op/inc.h"

#include "src/emulator/registers.h"
#include "src/emulator/util.h"

INC::INC(Target target) : target(target) {}

std::unique_ptr<Op> INC::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 3, 5));
    return std::make_unique<INC>(target);
}

std::string INC::Print() const {
    return "INC, target: " + ::Print(target);
}

void INC::ExecuteImpl(Registers& registers, Memory& memory) {
    auto [res, carry_per_bit] = OverflowingAdd(GetTarget(registers, memory, target), (uint8_t) 1);
    SetTarget(registers, memory, target, res);
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, carry_per_bit[3]);
}

INC_RR::INC_RR(RR_Target target) : target(target) {}

std::unique_ptr<Op> INC_RR::Decode(uint8_t op_code) {
    auto target = static_cast<RR_Target>(GetBitRange(op_code, 4, 5));
    return std::make_unique<INC_RR>(target);
}

std::string INC_RR::Print() const {
    return "INC_RR, target: " + ::Print(target);
}

void INC_RR::ExecuteImpl(Registers& registers, Memory& memory) {
    auto [res, carry_per_bit] = OverflowingAdd(GetRRTarget(registers, target), (uint16_t) 1);
    SetRRTarget(registers, target, res);
}

DEC::DEC(Target target) : target(target) {}

std::unique_ptr<Op> DEC::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 3, 5));
    return std::make_unique<DEC>(target);
}

std::string DEC::Print() const {
    return "DEC, target: " + ::Print(target);
}

void DEC::ExecuteImpl(Registers& registers, Memory& memory) {
    auto [res, carry_per_bit] = OverflowingSub(GetTarget(registers, memory, target), (uint8_t) 1);
    SetTarget(registers, memory, target, res);
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, true);
    registers.SetFlag(H_FLAG, carry_per_bit[3]);
}
