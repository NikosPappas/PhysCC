#pragma once

#include "parser/ast.hpp"

// =======================================
// PDE Classification
// =======================================
enum class PDEType {
    Elliptic,
    Parabolic,
    Hyperbolic,
    Quantum
};

// =======================================
// Semantic Result
// =======================================
struct SemanticInfo {
    PDEType type = PDEType::Elliptic;
};

// =======================================
// API
// =======================================
SemanticInfo analyze(const Equation& eq);

