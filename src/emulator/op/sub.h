#include "src/emulator/op/op_base.h"

#include "src/emulator/registers.h"
#include "src/emulator/memory.h"

#include <memory>

class SUB : public Op {
public:
    explicit SUB(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};

class SUB_N : public Op {
public:
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
};
