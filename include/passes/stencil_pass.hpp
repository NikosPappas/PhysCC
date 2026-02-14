#pragma once
#include "pass.hpp"
#include "parser/ast.hpp" // Needs Node definitions
#include "codegen/backend_ir.hpp" // Needs IntegratorIR definition

// 🟢 ADDED: Forward Declaration
struct CompilerContext;

class StencilPass : public Pass {
public:
    bool run(CompilerContext& ctx) override;

private:
    void analyzeExpression(const Node* node, EquationNode& eqNode);
};
