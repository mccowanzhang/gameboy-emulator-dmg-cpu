#pragma once

#include <cstdint>
#include <iostream>

class Registers;
class Memory;

class Op {
public:
    virtual ~Op() = default;
    void Execute(Registers& registers, Memory& memory);
    virtual std::string Print() const = 0;
    virtual void Print(std::ostream& os) const { os << Print(); }
    friend std::ostream& operator<<(std::ostream& os, const Op& op) {
        op.Print(os);
        return os;
    }
protected:
    virtual void ExecuteImpl(Registers& registers, Memory& memory) = 0;
};

enum Target : uint8_t {
    A = 0b111,
    B = 0b000,
    C = 0b001,
    D = 0b010,
    E = 0b011,
    H = 0b100,
    L = 0b101,
    HLI = 0b110,
};
std::string Print(Target target);

uint8_t GetNext8(Registers& registers, Memory& memory);
uint16_t GetNext16(Registers& registers, Memory& memory);
