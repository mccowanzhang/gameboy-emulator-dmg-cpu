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