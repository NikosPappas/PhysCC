#pragma once
#include "pass.hpp"
#include "parser/ast.hpp"

// Forward Declaration
struct CompilerContext;

class SemanticPass : public Pass {
public:
    bool run(CompilerContext& ctx) override;

private:
    // 🟢 ADDED: Declarations for the methods implemented in .cpp
    void analyzeSystem(const System& system);
    void checkExpression(const Node* node);
};
