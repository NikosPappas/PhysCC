#include "ast/printer.hpp"
#include <sstream>
#include <type_traits>

std::string ASTPrinter::print(const Equation& eq) {
    out.clear();
    out += "Equation\n";
    indent(1); out += "LHS:\n";
    printExpr(eq.lhs.get(), 2);
    indent(1); out += "RHS:\n";
    printExpr(eq.rhs.get(), 2);
    return out;
}

void ASTPrinter::indent(int n) {
    for (int i = 0; i < n; ++i) out += "  ";
}

void ASTPrinter::printExpr(const Expr* e, int indentLevel) {
    if (!e) {
        indent(indentLevel);
        out += "<null>\n";
        return;
    }

    // Number
    if (auto n = dynamic_cast<const NumberExpr*>(e)) {
        indent(indentLevel);
        out += "Number(" + std::to_string(n->value) + ")\n";
        return;
    }

    // Variable
    if (auto v = dynamic_cast<const VariableExpr*>(e)) {
        indent(indentLevel);
        out += "Variable(" + v->name + ")\n";
        return;
    }

    // Binary
    if (auto b = dynamic_cast<const BinaryExpr*>(e)) {
        indent(indentLevel);
        out += std::string("Binary('") + b->op + "')\n";
        indent(indentLevel + 1); out += "LHS:\n";
        printExpr(b->lhs.get(), indentLevel + 2);
        indent(indentLevel + 1); out += "RHS:\n";
        printExpr(b->rhs.get(), indentLevel + 2);
        return;
    }

    // Function call
    if (auto c = dynamic_cast<const CallExpr*>(e)) {
        indent(indentLevel);
        out += "Call(" + c->name + ")\n";
        indent(indentLevel + 1); out += "Arg:\n";
        printExpr(c->arg.get(), indentLevel + 2);
        return;
    }

    // Derivative
    if (auto d = dynamic_cast<const DerivativeExpr*>(e)) {
        indent(indentLevel);
        out += "Derivative(order=" + std::to_string(d->order) +
               ", var=" + d->var +
               ", wrt=" + d->wrt + ")\n";
        return;
    }
    if (auto* l = dynamic_cast<const LaplacianExpr*>(e)) {
        out << "lap(";
        printExpr(l->arg.get(), out);
        out << ")";
    }

    indent(indentLevel);
    out += "<unknown expr>\n";
}

