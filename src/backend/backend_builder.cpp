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
#include "backend/backend_builder.hpp"

BackendIR buildBackend(const IntegratorIR& ir)
{
    BackendIR b;

    // Minimal logic for now
    if(ir.scheme == TimeScheme::QuantumCrankNicolson)
        b.kind = BackendKind::MPI;
    else
        b.kind = BackendKind::OpenMP;

    return b;
}

