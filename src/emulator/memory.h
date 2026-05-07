#pragma once

#include <array>
#include <cstdint>

class Memory {
public:
    static constexpr size_t kMemorySize = 64 << 10; // 64 KB

    Memory();
    void Reset();

    uint8_t Read8(uint16_t addr) const;
    void Write8(uint16_t addr, uint8_t val);

    uint16_t Read16(uint16_t addr) const;
    void Write16(uint16_t addr, uint16_t val);

private:
    std::array<uint8_t, kMemorySize> memory_;
};