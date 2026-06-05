#include "src/emulator/op/add.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

void ADD(Registers& registers, uint8_t val) {
    auto [res, carry_per_bit] = OverflowingAdd<uint8_t>(registers.A, val);
    registers.A = res;
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, carry_per_bit[3]);
    registers.SetFlag(C_FLAG, carry_per_bit[7]);
}

void ADC(Registers& registers, uint8_t val) {
    auto [res1, carry_per_bit1] = OverflowingAdd<uint8_t>(
        val,
        static_cast<uint8_t>(registers.GetFlag(Flag::C_FLAG))
    );
    ADD(registers, res1);
}

ADD::ADD(Target target) : target(target) {}

std::unique_ptr<Op> ADD::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<ADD>(target);
}

void ADD::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = 0;
    switch (target) {
        case Target::A:
            val = registers.A;
            break;
        case Target::B:
            val = registers.B;
            break;
        case Target::C:
            val = registers.C;
            break;
        case Target::D:
            val = registers.D;
            break;
        case Target::E:
            val = registers.E;
            break;
        case Target::H:
            val = registers.H;
            break;
        case Target::L:
            val = registers.L;
            break;
        case Target::HLI:
            val = memory.Read8(registers.HL());
            break;
        default:
            LOG(FATAL) << "Unrecognized ADD target";
    }

    ::ADD(registers, val);
}

std::string ADD::Print() const {
    return "ADD, target: " + ::Print(target);
}

std::unique_ptr<Op> ADD_N::Decode(uint8_t op_code) {
    return std::make_unique<ADD_N>();
}

std::string ADD_N::Print() const {
    return "ADD_N";
}

void ADD_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t n = GetNext8(registers, memory);
    ::ADD(registers, n);
}

ADC::ADC(Target target) : target(target) {}

std::unique_ptr<Op> ADC::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<ADC>(target);
}

void ADC::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = 0;
    switch (target) {
        case Target::A:
            val = registers.A;
            break;
        case Target::B:
            val = registers.B;
            break;
        case Target::C:
            val = registers.C;
            break;
        case Target::D:
            val = registers.D;
            break;
        case Target::E:
            val = registers.E;
            break;
        case Target::H:
            val = registers.H;
            break;
        case Target::L:
            val = registers.L;
            break;
        case Target::HLI:
            val = memory.Read8(registers.HL());
            break;
        default:
            LOG(FATAL) << "Unrecognized ADC target\n";
    }

    ::ADC(registers, val);
}

std::string ADC::Print() const {
    return "ADC, target: " + ::Print(target);
}

std::unique_ptr<Op> ADC_N::Decode(uint8_t op_code) {
    return std::make_unique<ADC_N>();
}

std::string ADC_N::Print() const {
    return "ADC_N";
}

void ADC_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t n = GetNext8(registers, memory);
    ::ADC(registers, n);
}
