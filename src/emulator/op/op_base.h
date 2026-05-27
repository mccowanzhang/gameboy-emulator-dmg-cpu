#pragma once

#include <cstdint>
#include <iostream>

class Memory;
class Registers;

class Op {
public:
    virtual ~Op() = default;
    virtual void Execute(Memory& memory, Registers& registers) = 0;
    virtual std::string Print() const = 0;
    virtual void Print(std::ostream& os) const { os << Print(); }
    friend std::ostream& operator<<(std::ostream& os, const Op& op) {
        op.Print(os);
        return os;
    }
};
