#pragma once

#include "src/emulator/registers.h"

#include <cstdint>

class Memory;

class CPU {
public:
    explicit CPU(Memory& memory);
    void Reset();
    void Step();

    Memory& memory;
    Registers registers;
};