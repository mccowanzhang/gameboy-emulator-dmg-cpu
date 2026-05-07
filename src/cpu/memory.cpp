#include "memory.h"

Memory::Memory() {
    Reset();
}

void Memory::Reset() {
    memory_.fill(0);
}

uint8_t Memory::Read8(uint16_t addr) const {
    return memory_[addr];
}

void Memory::Write8(uint16_t addr, uint8_t val) {
    memory_[addr] = val;
}

uint16_t Memory::Read16(uint16_t addr) const {
    uint8_t low = memory_[addr];
    uint8_t high = memory_[addr + 1];

    return static_cast<uint16_t>((high << 8) | low);
}

void Memory::Write16(uint16_t addr, uint16_t val) {
    uint8_t low = val & 0xFF;
    memory_[addr] = low;
    uint8_t high = (val >> 8) & 0xFF;
    memory_[addr + 1] = high;
}