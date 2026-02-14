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
