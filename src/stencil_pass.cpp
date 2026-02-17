/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026  [Το Όνομά Σας]
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
#include "passes/stencil_pass.hpp"
#include <iostream>

void StencilPass::run(CompilerContext& ctx) {
    if (!ctx.system) return;

    std::cout << "[Stencil] Generating stencils for " << ctx.system->equations.size() << " equations...\n";

    // Loop through every equation in the system
    for (const auto& eq : ctx.system->equations) {
        Stencil stencil;
        stencil.targetVar = eq->varName;
        
        // Analyze the RHS of the equation
        analyzeExpression(eq->rhs.get(), stencil);

        // Store the stencil in the IR, keyed by variable name
        ctx.ir.stencils[eq->varName] = stencil;
    }
}

void StencilPass::analyzeExpression(const Node* node, Stencil& stencil) {
    if (!node) return;

    // Recursively handle binary operations (Sum/Difference)
    if (node->type() == NodeType::BinaryOp) {
        auto bin = static_cast<const BinaryOpNode*>(node);
        if (bin->op == '+' || bin->op == '-') {
            analyzeExpression(bin->left.get(), stencil);
            analyzeExpression(bin->right.get(), stencil);
            return;
        }
    }

    // Handle Laplacian Term: lap(u) -> 1*u[i+1] - 2*u[i] + 1*u[i-1]
    if (node->type() == NodeType::Laplacian) {
        auto lap = static_cast<const LaplacianNode*>(node);
        if (lap->target->type() == NodeType::Variable) {
            auto var = static_cast<const VariableNode*>(lap->target.get());
            // Standard 1D Finite Difference Stencil
            stencil.assign.terms.push_back({1.0, var->name, {1}});   // u[i+1]
            stencil.assign.terms.push_back({-2.0, var->name, {0}});  // u[i]
            stencil.assign.terms.push_back({1.0, var->name, {-1}});  // u[i-1]
        }
        return;
    }

    // Handle Scaled Laplacian: e.g., 0.16 * lap(u)
    if (node->type() == NodeType::BinaryOp) {
        auto bin = static_cast<const BinaryOpNode*>(node);
        if (bin->op == '*') {
            // Case: Number * Laplacian
            if (bin->left->type() == NodeType::Number && bin->right->type() == NodeType::Laplacian) {
                double coeff = static_cast<const NumberNode*>(bin->left.get())->value;
                auto lap = static_cast<const LaplacianNode*>(bin->right.get());
                auto var = static_cast<const VariableNode*>(lap->target.get());
                
                // Add scaled terms to stencil
                stencil.assign.terms.push_back({coeff * 1.0, var->name, {1}});
                stencil.assign.terms.push_back({coeff * -2.0, var->name, {0}});
                stencil.assign.terms.push_back({coeff * 1.0, var->name, {-1}});
            }
        }
    }
}
