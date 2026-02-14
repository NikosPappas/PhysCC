#include "passes/parse_pass.hpp"
#include "compiler/context.hpp"

bool ParsePass::run(CompilerContext& ctx) {
    // This pass is currently bypassed by main.cpp's direct parsing.
    // We return true to keep the build system happy.
    return true;
}
