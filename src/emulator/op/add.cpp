#include "src/emulator/op/add.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

std::unique_ptr<Op> ADD::Decode(uint8_t op_code) {
    // TODO: impl
    return nullptr;
}

void ADD::Execute(Memory& memory, Registers& registers) {
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

    uint8_t new_val;
    bool overflowed = OverflowingAdd<uint8_t>(registers.A, val, new_val);
    registers.SetFlag(Z_FLAG, new_val == 0);
    registers.SetFlag(N_FLAG, false);
    registers.SetFlag(H_FLAG, (registers.A & 0x0F) + (new_val & 0x0F) > 0x0F);
    registers.SetFlag(C_FLAG, overflowed);
    registers.A = new_val;
}

std::string ADD::Print() const {
    return "ADD";
}
