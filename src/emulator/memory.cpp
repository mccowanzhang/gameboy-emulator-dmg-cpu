#include "memory.h"

#include "absl/log/log.h"

#include <bitset>
#include <iostream>

Memory::Memory() {
    Reset();
}

void Memory::Reset() {
    LOG(INFO) << "Memory reset";
    memory_.fill(0);
}

uint8_t Memory::Read8(uint16_t addr) const {
    LOG(INFO) << "Read: " << std::bitset<8>(memory_[addr])
              << " at addr: " << std::hex << addr;
    return memory_[addr];
}

void Memory::Write8(uint16_t addr, uint8_t val) {
    LOG(INFO) << "Wrote: " << std::bitset<8>(val)
              << " at addr: " << std::hex << addr;
    memory_[addr] = val;
}

uint16_t Memory::Read16(uint16_t addr) const {
    uint8_t low = memory_[addr];
    uint8_t high = memory_[addr + 1];
    LOG(INFO) << "Read: " << std::bitset<16>(static_cast<uint16_t>((high << 8) | low))
              << " at addr: " << std::hex << addr; 
    return static_cast<uint16_t>((high << 8) | low);
}

void Memory::Write16(uint16_t addr, uint16_t val) {
    uint8_t low = val & 0xFF;
    memory_[addr] = low;
    uint8_t high = (val >> 8) & 0xFF;
    memory_[addr + 1] = high;
    LOG(INFO) << "Wrote: " << std::bitset<16>(val)
              << " at addr: " << std::hex << addr;
}

void Memory::WriteProgram(uint16_t addr, std::span<const uint8_t> program) {
    LOG(INFO) << "Wrote program of size: " << program.size()
              << " starting at addr: " << std::hex << addr;
    for (size_t i = 0; i < program.size(); ++i) {
        memory_[addr + i] = program[i];
    }
}