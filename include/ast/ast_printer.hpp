#pragma once
#include <string>
#include "ast.hpp"

struct ASTPrinter {
    std::string print(const Equation& eq);

private:
    void printExpr(const Expr* e, int indent);
    void indent(int n);

    std::string out;
};

