#pragma once
#include <memory>

class Pass;

std::unique_ptr<Pass> createParsePass();
std::unique_ptr<Pass> createSemanticPass();
std::unique_ptr<Pass> createStencilPass();
std::unique_ptr<Pass> createIntegratorPass();
std::unique_ptr<Pass> createBackendPass();
std::unique_ptr<Pass> createCodegenPass();

