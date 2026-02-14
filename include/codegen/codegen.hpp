#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "backend_ir.hpp"       // 🟢 Include the struct definition
#include "passes/stencil_pass.hpp" // For IntegratorIR

// Backend declarations
void emitCpp(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitSycl(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitMPI(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitCuda(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
void emitAVX2(const IntegratorIR& ir, const BackendIR& backend, std::ostream& out);
