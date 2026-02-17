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
#include "ir/timestep_builder.hpp"
#include "semantic/semantic.hpp"   // safe to include again

TimeStepIR buildTimeStep(const SemanticInfo& sem,
                         const StencilIR& stencil)
{
    TimeStepIR ts;
    ts.stencil = stencil;
    ts.dt = 0.01;

    switch (sem.type) {

        case PDEType::Elliptic:
            ts.scheme = TimeScheme::Jacobi;
            ts.iterations = 500;
            break;

        case PDEType::Parabolic:
            ts.scheme = TimeScheme::ExplicitEuler;
            ts.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ts.scheme = TimeScheme::Leapfrog;
            ts.iterations = 100;
            break;

        case PDEType::Quantum:
            ts.scheme = TimeScheme::QuantumEuler;
            ts.iterations = 100;
            break;
    }

    return ts;
}

