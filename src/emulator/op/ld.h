#include "src/emulator/op/op_base.h"

#include <memory>

class LD : public Op {
public:
    explicit LD(Target source, Target dest);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target source;
    Target dest;
};

class LD_R_N : public Op {
public:
    explicit LD_R_N(Target dest);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target dest;
};

enum LD_RR_Mode : uint8_t {
    BCI_A = 0b000,
    A_BCI = 0b001,
    DEI_A = 0b010,
    A_DEI = 0b011,
    HLPLUSI_A = 0b100,
    A_HLPLUSI = 0b101,
    HLMINUSI_A = 0b110,
    A_HLMINUSI = 0b111,
};
std::string Print(LD_RR_Mode mode);

class LD_RR : public Op {
public:
    explicit LD_RR(LD_RR_Mode mode);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    LD_RR_Mode mode;
};

enum LD_NNI_Mode : bool {
    NNI_A = 0b0,
    A_NNI = 0b1,
};
std::string Print(LD_NNI_Mode mode);

class LD_NNI : public Op {
public:
    explicit LD_NNI(LD_NNI_Mode mode);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    LD_NNI_Mode mode;
};

enum LDH_C_Mode : bool {
    CI_A = 0b0,
    A_CI = 0b1,
};
std::string Print(LDH_C_Mode mode);

class LDH_C : public Op {
public:
    explicit LDH_C(LDH_C_Mode mode);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    LDH_C_Mode mode;
};

enum LDH_NI_Mode : bool {
    NI_A = 0b0,
    A_NI = 0b1,
};
std::string Print(LDH_NI_Mode mode);

class LDH_NI : public Op {
public:
    explicit LDH_NI(LDH_NI_Mode mode);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    LDH_NI_Mode mode;
};
