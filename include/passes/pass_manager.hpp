/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026 Nikos Pappas
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
#include <vector>
#include <memory>
#include "passes/pass.hpp"
#include "compiler/context.hpp"

class PassManager {
public:
    // This template method allows pm.add<ParsePass>()
    template <typename T>
    void add() {
        passes.push_back(std::make_unique<T>());
    }

    void run(CompilerContext& ctx) {
        for (const auto& pass : passes) {
            pass->run(ctx);
        }
    }

private:
    std::vector<std::unique_ptr<Pass>> passes;
};
