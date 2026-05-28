#include "src/emulator/op/op.h"

#include "src/emulator/op/nop.h"

#include "absl/log/log.h"

std::unique_ptr<Op> ParseOp(uint8_t op_code) {
    switch (op_code) {
        case NOP::kOpCode: // NOP
            return std::make_unique<NOP>();
        default:
            LOG(INFO) << "Unknown op_code: " << op_code;
            return std::make_unique<NOP>();
    }
}