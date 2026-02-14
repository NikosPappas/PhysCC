#pragma once
#include "pass.hpp"

struct CompilerContext;

class CodegenPass : public Pass {
public:
    // 🟢 Change void -> bool
    bool run(CompilerContext& ctx) override;
};
