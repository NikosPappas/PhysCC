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
#pragma once

// ======================================================
// Physics Compiler — Pass Interface
//
// Every compiler stage becomes a Pass:
//
//   SemanticPass
//   StencilPass
//   IntegratorPass
//   BackendPass
//   CodegenPass
//
// Inspired by LLVM/MLIR pass design.
// ======================================================

#include "compiler/context.hpp"
#include <string>

class Pass {
public:
    virtual ~Pass() = default;

    // Human readable name (for debugging / pipelines)
    virtual const char* name() const = 0;

    // Execute pass
    virtual void run(CompilerContext& ctx) = 0;
};

