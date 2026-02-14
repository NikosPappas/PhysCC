#include "passes/semantic_pass.hpp"
#include "compiler/context.hpp"
#include <iostream>

// 🟢 Change void -> bool
bool SemanticPass::run(CompilerContext& ctx) {
    if (!ctx.system) return false;
    
    try {
        analyzeSystem(*ctx.system);
    } catch (const std::exception& e) {
        std::cerr << "[Semantic Error] " << e.what() << std::endl;
        return false;
    }
    
    return true;
}

void SemanticPass::analyzeSystem(const System& system) {
    for (const auto& eqn : system.equations) {
        checkExpression(eqn->expression.get());
    }
}

void SemanticPass::checkExpression(const Node* node) {
    // Basic recursion to check for nulls or invalid types
    if (!node) return;
    // In a real compiler, we'd check variable existence here
}
