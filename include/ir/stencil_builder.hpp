#pragma once
#include "parser/ast.hpp"
#include "ir/stencil_ir.hpp"
#include "semantic/semantic.hpp"
StencilIR buildStencil(const Equation& eq);

