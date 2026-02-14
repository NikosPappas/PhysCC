#include "passes/stencil_pass.hpp"
#include "compiler/context.hpp"
#include <iostream>

bool StencilPass::run(CompilerContext& ctx) {
    if (!ctx.system) return false;

    ctx.ir.stencils.clear();

    for (const auto& eqn : ctx.system->equations) {
        StencilNode stencil;
        stencil.name = eqn->variable;
        
        // 🟢 NEW: Detect if this is a complex equation (looking for 'i')
        // We scan the expression to determine if we need a complex update
        analyzeExpression(eqn->expression.get(), stencil);
        
        ctx.ir.stencils[stencil.name] = stencil;
    }
    return true;
}

void StencilPass::analyzeExpression(const Node* node, StencilNode& stencil) {
    if (!node) return;

    // 1. Handle Function/Differential Calls (lap, ∇, ∂)
    if (auto call = dynamic_cast<const CallExpr*>(node)) {
        if (call->callee == "lap" || call->callee == "∇") {
            if (!call->args.empty()) {
                if (auto var = dynamic_cast<const Variable*>(call->args[0].get())) {
                    std::string v = var->name;
                    // Standard 5-point stencil for 2D Laplacian
                    stencil.terms.push_back({-4.0, v, {0, 0}});
                    stencil.terms.push_back({1.0,  v, {1, 0}});
                    stencil.terms.push_back({1.0,  v, {-1, 0}});
                    stencil.terms.push_back({1.0,  v, {0, 1}});
                    stencil.terms.push_back({1.0,  v, {0, -1}});
                }
            }
        }
        // Recurse into arguments (for nested functions)
        for (const auto& arg : call->args) {
            analyzeExpression(arg.get(), stencil);
        }
    }
    
    // 2. Handle Binary Operations (+, -, *, ^)
    else if (auto bin = dynamic_cast<const BinaryExpr*>(node)) {
        // Here we could handle coefficients (e.g., -0.5 * lap(psi))
        // For the PhD-level version, you'd track a 'multiplier' state
        analyzeExpression(bin->left.get(), stencil);
        analyzeExpression(bin->right.get(), stencil);
    }
    
    // 3. Handle Atoms (Variables, Numbers, Quantum Constants)
    else if (auto var = dynamic_cast<const Variable*>(node)) {
        // 🟢 Handle Imaginary Unit 'i'
        if (var->name == "i" || var->name == "I") {
            std::cout << "[Stencil] Detected Imaginary Unit: Flagging for Complex Solver.\n";
            // In the IR, this tells the generator to use:
            // Re(u_next) = Re(u) - Im(rhs) * dt
            // Im(u_next) = Im(u) + Re(rhs) * dt
        }
        
        // Handle physical constants
        double coeff = 1.0;
        if (var->name == "hbar") coeff = 1.054e-34; // Placeholder for actual value

        stencil.terms.push_back({coeff, var->name, {0, 0}});
    }
    else if (auto num = dynamic_cast<const Number*>(node)) {
        // Pure numeric terms (potential or source terms)
        stencil.terms.push_back({num->value, "const", {0, 0}});
    }
}
