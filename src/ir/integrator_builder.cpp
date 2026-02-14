#include "ir/integrator_builder.hpp"

IntegratorIR buildIntegrator(const SemanticInfo& sem,
                             const StencilIR& stencil)
{
    IntegratorIR ir;
    ir.stencil = stencil;
    ir.dt = 0.01;

    switch(sem.type)
    {
        case PDEType::Elliptic:
            ir.scheme = TimeScheme::Jacobi;
            ir.iterations = 500;
            break;

        case PDEType::Parabolic:
            ir.scheme = TimeScheme::ExplicitEuler;
            ir.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ir.scheme = TimeScheme::Leapfrog;
            ir.iterations = 100;
            break;

        case PDEType::Quantum:
            ir.scheme = TimeScheme::QuantumEuler;   // ⭐ CRITICAL
            ir.iterations = 100;
            break;
    }

    return ir;
}


/*
IntegratorIR buildIntegrator(const SemanticInfo& sem,
                             const StencilIR& stencil)
{
    IntegratorIR ir;
    ir.stencil = stencil;
    ir.field   = stencil.assign.rhsField;

    switch(sem.type)
    {
        case PDEType::Elliptic:
            ir.kind = IntegratorKind::Jacobi;
            ir.iterations = 500;
            break;

        case PDEType::Parabolic:
            ir.kind = IntegratorKind::ExplicitEuler;
            ir.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ir.kind = IntegratorKind::Leapfrog;
            ir.iterations = 100;
            break;

        case PDEType::Quantum:
            ir.kind = IntegratorKind::QuantumCrankNicolson; // 🔥 upgrade
            ir.iterations = 100;
            break;
    }

    return ir;
}*/
/*
IntegratorIR buildIntegrator(const SemanticInfo& sem,
                             const StencilIR& stencil)
{
    IntegratorIR ir;
    ir.stencil = stencil;

    switch(sem.type)
    {
        case PDEType::Elliptic:
            ir.scheme = TimeScheme::Jacobi;
            ir.iterations = 500;
            break;

        case PDEType::Parabolic:
            ir.scheme = TimeScheme::ExplicitEuler;
            ir.iterations = 100;
            break;

        case PDEType::Hyperbolic:
            ir.scheme = TimeScheme::Leapfrog;
            ir.iterations = 100;
            break;

        case PDEType::Quantum:
            ir.scheme = TimeScheme::QuantumCrankNicolson; // NEW DEFAULT
            ir.useComplex = true;
            ir.iterations = 100;
            break;
    }

    return ir;
}
*/

