#pragma once

#include "src/emulator/registers.h"

#include <cstdint>

class Memory;

class CPU {
public:
    explicit CPU(Memory& memory);
    void Reset();
    void Step();
    Registers GetRegisters();

private:
    uint8_t Fetch8();
    uint16_t Fetch16();

    enum ArithTarget : uint8_t {
        A, B, C, D, E, H, L,
    };
    void ADD(ArithTarget target);

    Memory& memory_;
    Registers registers_;
};