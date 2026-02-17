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
#include <memory>
#include <iostream>
#include "parser/ast.hpp"
#include "codegen/backend_ir.hpp" // IntegratorIR is here

struct CompilerContext {
    std::unique_ptr<System> system;
    IntegratorIR ir;
    // std::ostream* output = &std::cout; // Optional, for python output
};
