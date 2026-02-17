/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026  [Το Όνομά Σας]
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
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

