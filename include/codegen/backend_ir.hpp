/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026 Nikos Pappas
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
#include <string>
#include <vector>
#include <map>
#include <iostream>

// --- Data Structures for Stencils ---

struct StencilTerm {
    double coefficient;
    std::string variable;
    struct { int x, y; } offset;
};

// Represents a resolved equation: du/dt = ...
struct StencilNode {
    std::string name;
    std::vector<StencilTerm> terms;
};

// Alias EquationNode to StencilNode so StencilPass works
using EquationNode = StencilNode;

// --- Data Structures for the Intermediate Representation (IR) ---

struct IntegratorIR {
    double dt = 0.01;
    std::string initial_condition = "zero";
      
    // Map of variable name -> Stencil Logic
    std::map<std::string, StencilNode> stencils;

    // Optimization flags
    struct Optimization {
        bool enableTiling = false;
        int tileSize = 16;
    } optimization;
};

// --- Data Structures for Backend Configuration ---

struct BackendIR {
    std::string init_type; 
    // Add other backend-specific flags here if needed
};
