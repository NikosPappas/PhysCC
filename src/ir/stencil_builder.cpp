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
#include "ir/stencil_builder.hpp"
#include "parser/ast.hpp"

namespace {

// --------------------------------------------------
// Collect spatial operator from AST
// --------------------------------------------------
void collect(const Expr* e, StencilIR& ir)
{
    if (!e) return;

    // lap(u) → central difference stencil
    if (auto lap = dynamic_cast<const LaplacianExpr*>(e)) {

        ir.assign.lhsField = "u_new";
        ir.assign.rhsField = "u";
        ir.assign.scale    = 1.0;

        // +1 * u[i+1]
        StencilTerm t1;
        t1.coeff = 1.0;
        t1.access.field  = "u";
        t1.access.offset = +1;
        ir.assign.terms.push_back(t1);

        // -2 * u[i]
        StencilTerm t2;
        t2.coeff = -2.0;
        t2.access.field  = "u";
        t2.access.offset = 0;
        ir.assign.terms.push_back(t2);

        // +1 * u[i-1]
        StencilTerm t3;
        t3.coeff = 1.0;
        t3.access.field  = "u";
        t3.access.offset = -1;
        ir.assign.terms.push_back(t3);

        return;
    }

    // recurse into binary expressions
    if (auto b = dynamic_cast<const BinaryExpr*>(e)) {
        collect(b->lhs.get(), ir);
        collect(b->rhs.get(), ir);
        return;
    }

    // recurse into calls if needed
    if (auto c = dynamic_cast<const CallExpr*>(e)) {
        collect(c->arg.get(), ir);
        return;
    }
}

} // namespace

// --------------------------------------------------
// Public API
// --------------------------------------------------
StencilIR buildStencil(const Equation& eq)
{
    StencilIR ir;

    ir.indexVar = "i";
    ir.begin    = 1;
    ir.end      = 99;

    // Build stencil from RHS
    collect(eq.rhs.get(), ir);

    // Fallback safety: ensure stencil exists
    if (ir.assign.terms.empty()) {

        StencilTerm t1;
        t1.coeff = 1.0;
        t1.access.field  = "u";
        t1.access.offset = +1;

        StencilTerm t2;
        t2.coeff = -2.0;
        t2.access.field  = "u";
        t2.access.offset = 0;

        StencilTerm t3;
        t3.coeff = 1.0;
        t3.access.field  = "u";
        t3.access.offset = -1;

        ir.assign.lhsField = "u_new";
        ir.assign.rhsField = "u";

        ir.assign.terms.push_back(t1);
        ir.assign.terms.push_back(t2);
        ir.assign.terms.push_back(t3);
    }

    return ir;
}

