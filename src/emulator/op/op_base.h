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
