#pragma once
#include "ir/stencil_ir.hpp"

enum class TimeScheme {
    None,
    Jacobi,      // Elliptic
    ExplicitEuler,
    Leapfrog,
    QuantumEuler,
    QuantumCrankNicolson
};

struct TimeStepIR {
    TimeScheme scheme = TimeScheme::None;

    int iterations = 100;
    double dt = 0.01;

    StencilIR stencil;
};

