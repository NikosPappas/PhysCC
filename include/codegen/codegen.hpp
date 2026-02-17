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
#include <iostream>
#include <vector>
#include <string>
#include "backend_ir.hpp"       // 🟢 Include the struct definition
#include "passes/stencil_pass.hpp" // For IntegratorIR

// Backend declarations
void emitCpp(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitSycl(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitMPI(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitCuda(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitAVX2(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
