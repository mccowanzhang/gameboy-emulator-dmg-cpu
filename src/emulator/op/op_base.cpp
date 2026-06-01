#include "src/emulator/op/op_base.h"

#include "absl/log/log.h"

void Op::Execute(Registers& registers, Memory& memory) {
    LOG(INFO) << "Executing " << Print();
    ExecuteImpl(registers, memory);
}