/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026  Nikos Pappas
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
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
