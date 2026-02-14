#pragma once
#include "semantic/semantic.hpp"
#include "ir/stencil_ir.hpp"
#include "ir/integrator_ir.hpp"

IntegratorIR buildIntegrator(const SemanticInfo& sem,
                             const StencilIR& stencil);

