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
#include "ir/integrator_builder.hpp"

IntegratorIR buildIntegrator(const SemanticInfo& sem,
                             const StencilIR& stencil)
{
    IntegratorIR ir;
    ir.stencil = stencil;
    ir.dt = 0.01;

    switch(sem.type)
    {
        case PDEType::Elliptic:
            ir.scheme = TimeScheme::Jacobi;
            ir.iterations = 500;
            break;

        case PDEType::Parabolic:
            ir.scheme = TimeScheme::ExplicitEuler;
            ir.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ir.scheme = TimeScheme::Leapfrog;
            ir.iterations = 100;
            break;

        case PDEType::Quantum:
            ir.scheme = TimeScheme::QuantumEuler;   // ⭐ CRITICAL
            ir.iterations = 100;
            break;
    }

    return ir;
}


/*
IntegratorIR buildIntegrator(const SemanticInfo& sem,
                             const StencilIR& stencil)
{
    IntegratorIR ir;
    ir.stencil = stencil;
    ir.field   = stencil.assign.rhsField;

    switch(sem.type)
    {
        case PDEType::Elliptic:
            ir.kind = IntegratorKind::Jacobi;
            ir.iterations = 500;
            break;

        case PDEType::Parabolic:
            ir.kind = IntegratorKind::ExplicitEuler;
            ir.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ir.kind = IntegratorKind::Leapfrog;
            ir.iterations = 100;
            break;

        case PDEType::Quantum:
            ir.kind = IntegratorKind::QuantumCrankNicolson; // 🔥 upgrade
            ir.iterations = 100;
            break;
    }

    return ir;
}*/
/*
IntegratorIR buildIntegrator(const SemanticInfo& sem,
                             const StencilIR& stencil)
{
    IntegratorIR ir;
    ir.stencil = stencil;

    switch(sem.type)
    {
        case PDEType::Elliptic:
            ir.scheme = TimeScheme::Jacobi;
            ir.iterations = 500;
            break;

        case PDEType::Parabolic:
            ir.scheme = TimeScheme::ExplicitEuler;
            ir.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ir.scheme = TimeScheme::Leapfrog;
            ir.iterations = 100;
            break;

        case PDEType::Quantum:
            ir.scheme = TimeScheme::QuantumCrankNicolson; // NEW DEFAULT
            ir.useComplex = true;
            ir.iterations = 100;
            break;
    }

    return ir;
}
*/

