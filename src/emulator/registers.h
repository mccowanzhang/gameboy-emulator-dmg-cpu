#pragma once

#include "src/emulator/util.h"

#include <cstdint> 

enum Flag : uint8_t {
    Z_FLAG = 1 << 7, // zero
    N_FLAG = 1 << 6, // subtract
    H_FLAG = 1 << 5, // half carry
    C_FLAG = 1 << 4, // carry
};

class Registers {
private:
    uint8_t F = 0; // Flags
public:
    // Special purpose registers
    uint16_t PC = 0; // Program Counter
    uint16_t SP = 0; // Stack Pointer
    uint8_t A = 0; // Accumulator
    uint8_t IR = 0; // Instruction Register
    uint8_t IE = 0; // Interrupt Enable
    // General registers
    uint8_t B = 0;
    uint8_t C = 0;
    uint8_t D = 0;
    uint8_t E = 0;
    uint8_t H = 0;
    uint8_t L = 0;

    uint8_t GetF() const { return F; }
    void SetF(uint8_t val) { F = (val & 0xF0); } // bits 0:3 always 0
    bool GetFlag(Flag flag) { return (F & flag) != 0; }
    void SetFlag(Flag flag, bool flag_val) { SetF(flag_val ? (F | flag) : (F & ~flag)); }

    uint16_t AF() const { return Promote(F, A); }
    uint16_t BC() const { return Promote(C, B); }
    uint16_t DE() const { return Promote(E, D); }
    uint16_t HL() const { return Promote(L, H); }

    void SetAF(uint8_t A_val, uint8_t F_val) { A = A_val; SetF(F_val); }
    void SetAF(uint16_t val) { SetAF(MSB(val), LSB(val));}
    void SetBC(uint8_t B_val, uint8_t C_val) { B = B_val; C = C_val; }
    void SetBC(uint16_t val) { SetBC(MSB(val), LSB(val));}
    void SetDE(uint8_t D_val, uint8_t E_val) { D = D_val; E = E_val; }
    void SetDE(uint16_t val) { SetDE(MSB(val), LSB(val));}
    void SetHL(uint8_t H_val, uint8_t L_val) { H = H_val; L = L_val; }
    void SetHL(uint16_t val) { SetHL(MSB(val), LSB(val));}
    void IncHL() { SetHL(HL() + 1); }
    void DecHL() { SetHL(HL() - 1); }

    bool operator==(const Registers& other) const {
        return PC == other.PC &&
               SP == other.SP &&
               A == other.A &&
               IR == other.IR &&
               IE == other.IE && 
               B == other.B && 
               C == other.C &&
               D == other.D && 
               E == other.E &&
               F == other.GetF() &&
               H == other.H &&
               L == other.L;
    }
    bool operator!=(const Registers& other) const {
        return !(*this == other);
    }
};

