#pragma once

#include <iostream>

class Memory;
class Registers;

class Op {
public:
    virtual ~Op() = default;
    virtual void Execute(Memory& memory, Registers& registers) = 0;
    virtual void Print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Op& op) {
        op.Print(os);
        return os;
    }
};

class NOP : public Op {
public:
    void Execute(Memory& memory, Registers& registers) override;
    void Print(std::ostream& os) const override;
};