#include "backend/backend_builder.hpp"

BackendIR buildBackend(const IntegratorIR& ir)
{
    BackendIR b;

    // Minimal logic for now
    if(ir.scheme == TimeScheme::QuantumCrankNicolson)
        b.kind = BackendKind::MPI;
    else
        b.kind = BackendKind::OpenMP;

    return b;
}

