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
