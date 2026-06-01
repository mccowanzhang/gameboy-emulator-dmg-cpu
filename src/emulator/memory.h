#pragma once

#include <array>
#include <cstdint>
#include <span>

class Memory {
public:
    static constexpr size_t kMemorySize = 64 << 10; // 64 KB

    Memory();
    void Reset();

    uint8_t Read8(uint16_t addr) const;
    void Write8(uint16_t addr, uint8_t val);

    uint16_t Read16(uint16_t addr) const;
    void Write16(uint16_t addr, uint16_t val);

    void WriteProgram(uint16_t addr, std::span<const uint8_t> program);

private:
    // from index 0x0000 to index 0x00FF) hard coded bootstrap code,
    // 0x100 to 0x3FFF are cartridge contents
    std::array<uint8_t, kMemorySize> memory_;
};