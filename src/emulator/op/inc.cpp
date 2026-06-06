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
