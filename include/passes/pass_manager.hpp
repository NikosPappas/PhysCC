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
