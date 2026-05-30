#include "src/emulator/op/decoder.h"

#include "src/emulator/op/nop.h"

#include "absl/log/log.h"


std::unique_ptr<Op> DecodeNOP(uint8_t op_code) {
    return std::make_unique<NOP>();
}

std::unique_ptr<Op> DecodeADD(uint8_t op_code) {
    return std::make_unique<NOP>();
}

std::unique_ptr<Op> DecodeOp(uint8_t op_code) {
    for (const auto& rule : kDecodeRules) {
        if ((op_code & rule.mask) == rule.value) {
            return rule.decoder(op_code);
        }
    }

    LOG(INFO) << "Unknown op_code: " << op_code;
    return std::make_unique<NOP>();
}