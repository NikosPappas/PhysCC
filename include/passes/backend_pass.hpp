#pragma once
#include "passes/pass.hpp"
#include "backend/backend_builder.hpp"

class BackendPass : public Pass {
public:
    void run(CompilerContext& ctx) override;
    const char* name() const override { return "BackendPass"; }
};
