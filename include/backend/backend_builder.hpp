#pragma once
#include "backend/backend_ir.hpp"
#include "ir/integrator_ir.hpp"

BackendIR buildBackend(const IntegratorIR& ir);

