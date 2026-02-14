#pragma once
#include "parser/ast.hpp"
#include <ostream>

class ASTPrinter {
public:
    explicit ASTPrinter(std::ostream& out) : out(out) {}
    
    void print(const System& system);
    void printEquation(const Equation& eq);
    void printNode(const Node* node);

private:
    std::ostream& out;
};
