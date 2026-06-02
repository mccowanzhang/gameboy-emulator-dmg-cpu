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

LD_R_N::LD_R_N(Target dest) : dest(dest) {}

std::unique_ptr<Op> LD_R_N::Decode(uint8_t op_code) {
    auto dest = static_cast<Target>(GetBitRange(op_code, 3, 5));
    return std::make_unique<LD_R_N>(dest);
}

std::string LD_R_N::Print() const {
    return "LD_R_N, dest: " + ::Print(dest);
}

void LD_R_N::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t val = ::GetNext8(registers, memory);

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

std::string Print(LD_RR_Mode mode) {
    switch (mode) {
        case BCI_A:
            return "BCI_A";
        case A_BCI:
            return "A_BCI";
        case DEI_A:
            return "DEI_A";
        case A_DEI:
            return "A_DEI";
        case HLPLUSI_A:
            return "HLPLUSI_A";
        case A_HLPLUSI:
            return "A_HLPLUSI";
        case HLMINUSI_A:
            return "HLMINUSI_A";
        case A_HLMINUSI:
            return "A_HLMINUSI";
        default:
            return "Unrecognized LD RR mode";
    }
}

LD_RR::LD_RR(LD_RR_Mode mode) : mode(mode) {}

std::unique_ptr<Op> LD_RR::Decode(uint8_t op_code) {
    auto mode = static_cast<LD_RR_Mode>(GetBitRange(op_code, 3, 5));
    return std::make_unique<LD_RR>(mode);
}

void LD_RR::ExecuteImpl(Registers& registers, Memory& memory) {
    switch (mode) {
        case BCI_A:
            memory.Write8(registers.BC(), registers.A);
            break;
        case A_BCI:
            registers.A = memory.Read8(registers.BC());
            break;
        case DEI_A:
            memory.Write8(registers.DE(), registers.A);
            break;
        case A_DEI:
            registers.A = memory.Read8(registers.DE());
            break;
        case HLPLUSI_A:
            memory.Write8(registers.HL(), registers.A);
            registers.IncHL();
            break;
        case A_HLPLUSI:
            registers.A = memory.Read8(registers.HL());
            registers.IncHL();
            break;
        case HLMINUSI_A:
            memory.Write8(registers.HL(), registers.A);
            registers.DecHL();
            break;
        case A_HLMINUSI:
            registers.A = memory.Read8(registers.HL());
            registers.DecHL();
            break;
        default:
            LOG(FATAL) << "Unrecognized LD RR mode";
    }
}

std::string LD_RR::Print() const {
    return "LD_RR, mode: " + ::Print(mode);
}
