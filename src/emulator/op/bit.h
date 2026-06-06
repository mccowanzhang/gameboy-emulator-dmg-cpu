#include "src/emulator/op/op_base.h"

#include "src/emulator/memory.h"
#include "src/emulator/registers.h"

#include <memory>

class CP : public Op {
public:
    explicit CP(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};

class CP_N : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};

class AND : public Op {
public:
    explicit AND(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};

class AND_N : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};

class OR : public Op {
public:
    explicit OR(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};

class OR_N : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};

class XOR : public Op {
public:
    explicit XOR(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};

class XOR_N : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};

class CCF : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};

class SCF : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};
    