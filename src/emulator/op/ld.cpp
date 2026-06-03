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

std::string Print(LD_NNI_Mode mode) {
    switch (mode) {
        case NNI_A:
            return "NNI_A";
        case A_NNI:
            return "A_NNI";
        default:
            return "Unrecognized LD NNI mode";
    }
}

LD_NNI::LD_NNI(LD_NNI_Mode mode) : mode(mode) {}

std::unique_ptr<Op> LD_NNI::Decode(uint8_t op_code) {
    auto mode = static_cast<LD_NNI_Mode>(GetBitRange(op_code, 4, 4));
    return std::make_unique<LD_NNI>(mode);
}

void LD_NNI::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t lsb = GetNext8(registers, memory);
    uint8_t msb = GetNext8(registers, memory);
    uint16_t nn = Promote(lsb, msb);
    switch (mode) {
        case NNI_A:
            memory.Write8(nn, registers.A);
            break;
        case A_NNI:
            registers.A = memory.Read8(nn);
            break;
        default:
            LOG(FATAL) << "Unrecognized LD NNI mode";
    }
}

std::string LD_NNI::Print() const {
    return "LD_NNI, mode: " + ::Print(mode);
}

std::string Print(LDH_C_Mode mode) {
    switch (mode) {
        case CI_A:
            return "CI_A";
        case A_CI:
            return "A_CI";
        default:
            return "Unrecognized LDH C mode";
    }
}

LDH_C::LDH_C(LDH_C_Mode mode) : mode(mode) {}

std::unique_ptr<Op> LDH_C::Decode(uint8_t op_code) {
    auto mode = static_cast<LDH_C_Mode>(GetBitRange(op_code, 4, 4));
    return std::make_unique<LDH_C>(mode);
}

std::string LDH_C::Print() const {
    return "LDH_C, mode: " + ::Print(mode);
}

void LDH_C::ExecuteImpl(Registers& registers, Memory& memory) {
    uint16_t addr = PromoteH(registers.C);
    switch (mode) {
        case CI_A:
            memory.Write8(addr, registers.A);
            break;
        case A_CI:
            registers.A = memory.Read8(addr);
            break;
        default:
            LOG(FATAL) << "Unknown LDH C mode";
    }
}

std::string Print(LDH_NI_Mode mode){
    switch (mode) {
        case NI_A:
            return "NI_A";
        case A_NI:
            return "A_NI";
        default:
            return "Unrecognized LDH NI mode";
    }
}

LDH_NI::LDH_NI(LDH_NI_Mode mode) : mode(mode) {}

std::unique_ptr<Op> LDH_NI::Decode(uint8_t op_code) {
    auto mode = static_cast<LDH_NI_Mode>(GetBitRange(op_code, 4, 4));
    return std::make_unique<LDH_NI>(mode);
}

std::string LDH_NI::Print() const {
    return "LDH_NI, mode: " + ::Print(mode);
}

void LDH_NI::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t n = GetNext8(registers, memory);
    uint16_t addr = PromoteH(n);
    switch (mode) {
        case NI_A:
            memory.Write8(addr, registers.A);
            break;
        case A_NI:
            registers.A = memory.Read8(addr);
            break;
        default:
            LOG(FATAL) << "Unrecognized LDH NI mode";
    }
}

std::string Print(LD_RR_NN_Target target) {
    switch (target) {
        case BC:
            return "BC";
        case DE:
            return "DE";
        case HL:
            return "HL";
        case SP:
            return "SP";
        default:
            return "Unrecognized LD RR NN target";
    }
}

LD_RR_NN::LD_RR_NN(LD_RR_NN_Target target) : target(target) {}

std::unique_ptr<Op> LD_RR_NN::Decode(uint8_t op_code) {
    auto target = static_cast<LD_RR_NN_Target>(GetBitRange(op_code, 4, 5));
    return std::make_unique<LD_RR_NN>(target);
}

std::string LD_RR_NN::Print() const {
    return "LD_RR_NN, target: " + ::Print(target);
}

void LD_RR_NN::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t lsb = GetNext8(registers, memory);
    uint8_t msb = GetNext8(registers, memory);
    uint16_t nn = Promote(lsb, msb);

    switch (target) {
        case BC:
            registers.SetBC(nn);
            break;
        case DE:
            registers.SetDE(nn);
            break;
        case HL:
            registers.SetHL(nn);
            break;
        case SP:
            registers.SP = nn;
            break;
    }
}

std::unique_ptr<Op> LD_NNI_SP::Decode(uint8_t op_code) {
    return std::make_unique<LD_NNI_SP>();
}

std::string LD_NNI_SP::Print() const {
    return "LD_NNI_SP";
}

void LD_NNI_SP::ExecuteImpl(Registers& registers, Memory& memory) {
    uint8_t lsb = GetNext8(registers, memory);
    uint8_t msb = GetNext8(registers, memory);
    uint16_t nn = Promote(lsb, msb);
    memory.Write16(nn, registers.SP);
}

std::unique_ptr<Op> LD_SP_HL::Decode(uint8_t op_code) {
    return std::make_unique<LD_SP_HL>();
}

std::string LD_SP_HL::Print() const {
    return "LD_SP_HL";
}

void LD_SP_HL::ExecuteImpl(Registers& registers, Memory& memory) {
    registers.SP = registers.HL();
}

std::unique_ptr<Op> LD_HL_SPE::Decode(uint8_t op_code) {
    return std::make_unique<LD_HL_SPE>();
}

std::string LD_HL_SPE::Print() const {
    return "LD_HL_SPE";
}

void LD_HL_SPE::ExecuteImpl(Registers& registers, Memory& memory) {
    auto e = static_cast<int8_t>(GetNext8(registers, memory));
    auto [res, carries_per_bit] = OverflowingAdd(
        registers.SP,
        static_cast<uint16_t>(static_cast<int16_t>(e))
    );

    registers.SetHL(res);
    registers.SetFlag(Flag::Z_FLAG, false);
    registers.SetFlag(Flag::N_FLAG, false);
    registers.SetFlag(Flag::H_FLAG, carries_per_bit[3]);
    registers.SetFlag(Flag::C_FLAG, carries_per_bit[7]);
}
