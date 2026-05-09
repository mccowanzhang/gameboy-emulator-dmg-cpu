#include "src/emulator/op.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"

void NOP::Execute(Memory& memory, Registers& registers) {
    return;
}

void NOP::Print(std::ostream& os) const {
    os << "NOP" << "\n";
}