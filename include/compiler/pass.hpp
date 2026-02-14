#pragma once

// ======================================================
// Physics Compiler — Pass Interface
//
// Every compiler stage becomes a Pass:
//
//   SemanticPass
//   StencilPass
//   IntegratorPass
//   BackendPass
//   CodegenPass
//
// Inspired by LLVM/MLIR pass design.
// ======================================================

#include "compiler/context.hpp"
#include <string>

class Pass {
public:
    virtual ~Pass() = default;

    // Human readable name (for debugging / pipelines)
    virtual const char* name() const = 0;

    // Execute pass
    virtual void run(CompilerContext& ctx) = 0;
};

