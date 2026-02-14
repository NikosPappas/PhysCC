#pragma once
#include <memory>
#include <string>

// =====================
// Base Expression
// =====================
struct Expr {
    virtual ~Expr() = default;
};

// =====================
// Literals & Variables
// =====================
struct NumberExpr : Expr {
    double value;
};

struct VariableExpr : Expr {
    std::string name;
};

// =====================
// Binary Operations
// =====================
struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};

// =====================
// Function Call
// =====================
struct CallExpr : Expr {
    std::string name;
    std::unique_ptr<Expr> arg;
};

// =====================
// Derivative
// =====================
struct DerivativeExpr : Expr {
    std::string var;   // u
    std::string wrt;   // t, x, y
    int order;         // 1, 2, ...
};

// =====================
// Equation
// =====================
struct Equation {
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};

