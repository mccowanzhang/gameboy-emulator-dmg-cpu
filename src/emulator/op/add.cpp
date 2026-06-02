#include "src/emulator/op/add.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

ADD::ADD(Target target) : target(target) {}

std::unique_ptr<Op> ADD::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<ADD>(target);
}

void ADD::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = 0;
    switch (target) {
        case A:
            val = registers.A;
            break;
        case B:
            val = registers.B;
            break;
        case C:
            val = registers.C;
            break;
        case D:
            val = registers.D;
            break;
        case E:
            val = registers.E;
            break;
        case H:
            val = registers.H;
            break;
        case L:
            val = registers.L;
            break;
        case HLI:
            val = memory.Read8(registers.HL());
            break;
        default:
            LOG(FATAL) << "Unrecognized ADD target\n";
    }

    auto [res, carry_per_bit] = OverflowingAdd<uint8_t>(registers.A, val);
    registers.A = res;
    registers.SetFlag(Z_FLAG, res == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, carry_per_bit[3]);
    registers.SetFlag(C_FLAG, carry_per_bit[7]);
}

std::string ADD::Print() const {
    return "ADD, target: " + ::Print(target);
}


ADC::ADC(Target target) : target(target) {}

std::unique_ptr<Op> ADC::Decode(uint8_t op_code) {
    auto target = static_cast<Target>(GetBitRange(op_code, 0, 2));
    return std::make_unique<ADC>(target);
}

void ADC::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = 0;
    switch (target) {
        case A:
            val = registers.A;
            break;
        case B:
            val = registers.B;
            break;
        case C:
            val = registers.C;
            break;
        case D:
            val = registers.D;
            break;
        case E:
            val = registers.E;
            break;
        case H:
            val = registers.H;
            break;
        case L:
            val = registers.L;
            break;
        case HLI:
            val = memory.Read8(registers.HL());
            break;
        default:
            LOG(FATAL) << "Unrecognized ADC target\n";
    }

    auto [res1, carry_per_bit1] = OverflowingAdd<uint8_t>(registers.A, val);
    auto [res2, carry_per_bit2] = OverflowingAdd<uint8_t>(
        res1, 
        static_cast<uint8_t>(registers.GetFlag(Flag::C_FLAG))
    );
    registers.A = res2;
    registers.SetFlag(Z_FLAG, res2 == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, carry_per_bit1[3] || carry_per_bit2[3]);
    registers.SetFlag(C_FLAG, carry_per_bit1[7] || carry_per_bit1[7]);
}

std::string ADC::Print() const {
    return "ADC, target: " + ::Print(target);
}
