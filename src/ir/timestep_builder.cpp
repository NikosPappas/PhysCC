#include "ir/timestep_builder.hpp"
#include "semantic/semantic.hpp"   // safe to include again

TimeStepIR buildTimeStep(const SemanticInfo& sem,
                         const StencilIR& stencil)
{
    TimeStepIR ts;
    ts.stencil = stencil;
    ts.dt = 0.01;

    switch (sem.type) {

        case PDEType::Elliptic:
            ts.scheme = TimeScheme::Jacobi;
            ts.iterations = 500;
            break;

        case PDEType::Parabolic:
            ts.scheme = TimeScheme::ExplicitEuler;
            ts.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ts.scheme = TimeScheme::Leapfrog;
            ts.iterations = 100;
            break;

        case PDEType::Quantum:
            ts.scheme = TimeScheme::QuantumEuler;
            ts.iterations = 100;
            break;
    }

    return ts;
}

