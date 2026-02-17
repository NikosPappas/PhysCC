/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026  Nikos Pappas
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


// 🟢 ADDED: Forward Declaration
struct CompilerContext;

class Pass {
public:
    virtual ~Pass() = default;
    
    // 🟢 CHANGED: Returns bool (true = success)
    virtual bool run(CompilerContext& ctx) = 0;
};
