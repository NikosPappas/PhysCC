#pragma once
#include <string>

// ======================================================
// Backend execution model
// ======================================================

enum class BackendKind {
    Serial,
    OpenMP,
    MPI
};

struct BackendIR {
    BackendKind kind = BackendKind::Serial;
};

