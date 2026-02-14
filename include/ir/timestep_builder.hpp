#pragma once
#include "semantic/semantic.hpp"
#include "ir/timestep_ir.hpp"

TimeStepIR buildTimeStep(const SemanticInfo& sem,
                         const StencilIR& stencil);

