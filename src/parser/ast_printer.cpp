/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026 Nikos Pappas
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
#include "parser/ast_printer.hpp"
#include <iostream>

void ASTPrinter::print(const System& system) {
    for (const auto& eq : system.equations) {
        printEquation(*eq);
        std::cout << std::endl;
    }
}

void ASTPrinter::printEquation(const Equation& eq) {
    // 🟢 FIX: Use .variable and .expression
    std::cout << "d" << eq.variable << "/dt = ";
    printNode(eq.expression.get());
}

void ASTPrinter::printNode(const Node* node) {
    if (!node) return;

    // 🟢 FIX: Use dynamic_cast instead of missing enums
    if (auto b = dynamic_cast<const BinaryExpr*>(node)) {
        std::cout << "(";
        printNode(b->left.get());
        std::cout << " " << b->op << " ";
        printNode(b->right.get());
        std::cout << ")";
    }
    else if (auto n = dynamic_cast<const Number*>(node)) {
        std::cout << n->value;
    }
    else if (auto v = dynamic_cast<const Variable*>(node)) {
        std::cout << v->name;
    }
    else if (auto c = dynamic_cast<const CallExpr*>(node)) {
        std::cout << c->callee << "(";
        for (size_t i = 0; i < c->args.size(); ++i) {
            printNode(c->args[i].get());
            if (i < c->args.size() - 1) std::cout << ", ";
        }
        std::cout << ")";
    }
    else {
        std::cout << "[Unknown Node]";
    }
}
