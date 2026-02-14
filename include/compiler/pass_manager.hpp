#pragma once

// ======================================================
// Physics Compiler — Pass Manager
//
// Runs a sequence of passes over CompilerContext.
// This becomes your compiler pipeline driver.
//
// Example:
//
//   PassManager pm;
//   pm.add(new SemanticPass());
//   pm.add(new StencilPass());
//   pm.run(ctx);
//
// ======================================================

#include "compiler/pass.hpp"
#include <vector>
#include <memory>
#include <iostream>

class PassManager {
public:
    PassManager() = default;

    // --------------------------------------------------
    // Add pass (takes ownership)
    // --------------------------------------------------
    void add(std::unique_ptr<Pass> pass) {
        passes.emplace_back(std::move(pass));
    }

    // --------------------------------------------------
    // Run all passes
    // --------------------------------------------------
    void run(CompilerContext& ctx) {
        for (auto& p : passes) {

            if (ctx.verbose) {
                std::cout << "[PASS] Running " << p->name() << "\n";
            }

            p->run(ctx);
        }
    }

private:
    std::vector<std::unique_ptr<Pass>> passes;
};

