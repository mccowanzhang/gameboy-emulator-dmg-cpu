#include "src/emulator/op/add.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

std::unique_ptr<Op> ADD::Decode(uint8_t op_code) {
    // TODO: impl
    return nullptr;
}

void ADD::Execute(Registers& registers, Memory& memory) {
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
    return "ADD";
}
