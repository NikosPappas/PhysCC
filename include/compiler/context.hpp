#pragma once
#include <memory>
#include <iostream>
#include "parser/ast.hpp"
#include "codegen/backend_ir.hpp" // IntegratorIR is here

struct CompilerContext {
    std::unique_ptr<System> system;
    IntegratorIR ir;
    // std::ostream* output = &std::cout; // Optional, for python output
};
