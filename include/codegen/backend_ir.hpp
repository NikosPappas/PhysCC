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
