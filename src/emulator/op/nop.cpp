#include "src/emulator/op/nop.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

void NOP::Execute(Memory& memory, Registers& registers) {
    return;
}

std::string NOP::Print() const {
    return "NOP";
}