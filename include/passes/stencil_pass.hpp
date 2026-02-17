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
