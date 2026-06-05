#pragma once

#include "src/emulator/op/op_base.h"

#include <memory>

namespace {
void ADD(Registers& registers, Memory& memory, uint8_t val);
} // namespace

class ADD : public Op {
public:
    explicit ADD(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};

class ADD_N : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};

class ADC : public Op {
public:
    explicit ADC(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};
