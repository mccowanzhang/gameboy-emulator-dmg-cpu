#include "src/emulator/op/nop.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"
#include "src/emulator/util.h"

#include "absl/log/log.h"

std::unique_ptr<Op> NOP::Decode(uint8_t op_code) {
    return std::make_unique<NOP>();
}

void NOP::Execute(Memory& memory, Registers& registers) {
    return;
}

std::string NOP::Print() const {
    return "NOP";
}