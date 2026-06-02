#include "src/emulator/op/op_base.h"

#include "absl/log/log.h"

void Op::Execute(Registers& registers, Memory& memory) {
    LOG(INFO) << "Executing " << Print();
    ExecuteImpl(registers, memory);
}

std::string Print(Target target) {
    switch (target) {
        case A:
            return "A";
        case B:
            return "B";
        case C:
            return "C";
        case D:
            return "D";
        case E:
            return "E";
        case H:
            return "H";
        case L:
            return "L";
        case HLI:
            return "HLI";
        default:
            return "Unrecognized target";
    }
}