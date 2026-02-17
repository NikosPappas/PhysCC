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
#include <string>
#include <vector>
#include <memory>
#include <iostream>

struct Node {
    virtual ~Node() = default;
};

struct BinaryExpr : public Node {
    std::unique_ptr<Node> left;
    std::string op;
    std::unique_ptr<Node> right;
    BinaryExpr(std::unique_ptr<Node> l, std::string o, std::unique_ptr<Node> r)
        : left(std::move(l)), op(o), right(std::move(r)) {}
};

struct Variable : public Node {
    std::string name;
    Variable(std::string n) : name(n) {}
};

struct Number : public Node {
    double value;
    Number(double v) : value(v) {}
};

struct CallExpr : public Node {
    std::string callee;
    std::vector<std::unique_ptr<Node>> args;
    CallExpr(std::string c, std::vector<std::unique_ptr<Node>> a)
        : callee(c), args(std::move(a)) {}
};

// 🟢 CRITICAL FIX: Members must be named 'variable' and 'expression'
struct Equation {
    std::string variable;            
    std::unique_ptr<Node> expression; 
    
    Equation(std::string v, std::unique_ptr<Node> e) 
        : variable(v), expression(std::move(e)) {}
};

struct System {
    std::vector<std::unique_ptr<Equation>> equations;
};
