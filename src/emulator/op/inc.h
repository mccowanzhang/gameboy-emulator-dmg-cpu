#include "src/emulator/op/op_base.h"

#include <memory>

class INC : public Op {
public:
    explicit INC(Target target);
    static std::unique_ptr<Op> Decode(uint8_t op_code);
    std::string Print() const override;
protected:
    void ExecuteImpl(Registers& registers, Memory& memory) override;
private:
    Target target;
};