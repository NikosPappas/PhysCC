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
#include <memory>
#include <string>

struct Expr {
    virtual ~Expr() = default;
};

struct NumberExpr : Expr {
    double value;
};

struct VariableExpr : Expr {
    std::string name;
};

struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};

struct Equation {
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};
struct CallExpr : Expr {
    std::string name;
    std::unique_ptr<Expr> arg;

    void print(int indent) const override;
};

