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

