#include "src/emulator/op/ld.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

LD::LD(Target source, Target dest) : source(source), dest(dest) {}

std::unique_ptr<Op> LD::Decode(uint8_t op_code) {
    auto source = static_cast<Target>(GetBitRange(op_code, 0, 2));
    auto dest = static_cast<Target>(GetBitRange(op_code, 3, 5));
    return std::make_unique<LD>(source, dest);
}

std::string LD::Print() const {
    return "LD, source: " + ::Print(source) + " dest: " + ::Print(dest);
}

void LD::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = 0;
    switch (source) {
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
            LOG(FATAL) << "Unrecognized source operand\n";
    }

    switch (dest) {
        case A:
            registers.A = val;
            break;
        case B:
            registers.B = val;
            break;
        case C:
            registers.C = val;
            break;
        case D:
            registers.D = val;
            break;
        case E:
            registers.E = val;
            break;
        case H:
            registers.H = val;
            break;
        case L:
            registers.L = val;
            break;
        case HLI:
            memory.Write8(registers.HL(), val);
            break;
        default:
            LOG(FATAL) << "Unrecognized dest operand\n";
    }
}