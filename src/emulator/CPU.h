#pragma once

#include "src/emulator/registers.h"

#include <cstdint>

class Memory;

class CPU {
public:
    explicit CPU(Memory& memory);
    void Reset();
    void Step();
    Registers GetRegisters() const;

private:
    uint8_t Fetch8();
    uint16_t Fetch16();

    Memory& memory_;
    Registers registers_;
};