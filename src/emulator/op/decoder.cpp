#include "src/emulator/op/decoder.h"

#include "src/emulator/op/nop.h"

#include "absl/log/log.h"

#include <bitset>

std::unique_ptr<Op> DecodeOp(uint8_t op_code) {
    for (const auto& rule : kDecodeRules) {
        if ((op_code & rule.mask) == rule.value) {
            return rule.decoder(op_code);
        }
    }

    LOG(INFO) << "Unknown op_code: " << std::bitset<8>(op_code);
    return std::make_unique<NOP>();
}