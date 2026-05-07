#pragma once

#include <cstdint> 

enum Flag : uint8_t {
    Z_FLAG = 1 << 7,
    N_FLAG = 1 << 6,
    H_FLAG = 1 << 5,
    C_FLAG = 1 << 4,
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

    uint8_t GetF() { return F; }
    void SetF(uint8_t val) { F = (val & 0xF0); } // bits 0:3 always 0
    bool GetFlag(Flag flag) { return (F & flag) != 0; }
    void SetFlag(Flag flag, bool flag_val) { SetF(flag_val ? (F | flag) : (F & ~flag)); }

    uint16_t AF() { return (A << 8) | F; }
    uint16_t BC() { return (B << 8) | C; }
    uint16_t DE() { return (D << 8) | E; }
    uint16_t HL() { return (H << 8) | L; }

    void SetAF(uint8_t A_val, uint8_t F_val) { A = A_val; SetF(F_val); }
    void SetAF(uint16_t val) { SetAF((val >> 8) & 0xFF, val & 0xFF);}
    void SetBC(uint8_t B_val, uint8_t C_val) { B = B_val; C = C_val; }
    void SetBC(uint16_t val) { SetBC((val >> 8) & 0xFF, val & 0xFF);}
    void SetDE(uint8_t D_val, uint8_t E_val) { D = D_val; E = E_val; }
    void SetDE(uint16_t val) { SetDE((val >> 8) & 0xFF, val & 0xFF);}
    void SetHL(uint8_t H_val, uint8_t L_val) { H = H_val; L = L_val; }
    void SetHL(uint16_t val) { SetHL((val >> 8) & 0xFF, val & 0xFF);}
};

