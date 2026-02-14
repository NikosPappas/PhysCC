#pragma once
#include "pass.hpp"

struct CompilerContext;

class ParsePass : public Pass {
public:
    bool run(CompilerContext& ctx) override; 
};
