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
#ifndef INTEGRATOR_IR_HPP
#define INTEGRATOR_IR_HPP

#include <string>
#include <vector>
#include <map>

struct StencilTerm {
    double coeff;
    std::string varName;
    struct { int x, y; } offset; // Simplified offset structure
};

struct EquationNode {
    std::string targetVar;
    // We'll use 'terms' directly to match your codegen logic
    std::vector<StencilTerm> terms;
};

struct OptimizationSettings {
    bool enableTiling = false;
    int tileSize = 64;
};

struct IntegratorIR {
    double dt = 0.05;
    std::string initial_condition = "square";
    
    // This is the map the compiler uses to generate the loops
    std::map<std::string, EquationNode> stencils;
    OptimizationSettings optimization;
};

#endif
