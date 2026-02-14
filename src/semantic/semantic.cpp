#include "semantic/semantic.hpp"
#include <stdexcept>
#include <iostream>
// ======================================================
// Internal helpers
// ======================================================

namespace {

// ------------------------------------------------------
// Scan AST for derivative info
// ------------------------------------------------------
struct ScanResult {
    bool hasTimeDerivative = false;
    int  maxTimeOrder      = 0;
    bool hasPsi            = false;
    bool hasLaplacianPsi = false;  
};

// recursive visitor
void scanExpr(const Expr* e, ScanResult& r)
{
    //if (!e) return;
     if (!e) return;

    if (auto d = dynamic_cast<const DerivativeExpr*>(e)) {

        std::cout << "[SEM] derivative var=" << d->var
                  << " wrt=" << d->wrt
                  << " order=" << d->order << "\n";

        if (d->wrt == "t") {
            r.hasTimeDerivative = true;
            if (d->order > r.maxTimeOrder)
                r.maxTimeOrder = d->order;
        }

        if (d->var == "psi")
            r.hasPsi = true;

        return;
    }

    // -------------------------
    // Derivative
    // -------------------------
    if (auto d = dynamic_cast<const DerivativeExpr*>(e)) {

        // detect time derivative
        if (d->wrt == "t") {
            r.hasTimeDerivative = true;
            if (d->order > r.maxTimeOrder)
                r.maxTimeOrder = d->order;
        }

        // detect quantum wavefunction
        if (d->var == "psi")
            r.hasPsi = true;

        return;
    }

    // -------------------------
    // Variable
    // -------------------------
    if (auto v = dynamic_cast<const VariableExpr*>(e)) {
        if (v->name == "psi")
            r.hasPsi = true;
        return;
    }

    // -------------------------
    // Function call
    // -------------------------
    if (auto c = dynamic_cast<const CallExpr*>(e)) {
        scanExpr(c->arg.get(), r);
        return;
    }

    // -------------------------
    // Laplacian
    // -------------------------
    if (auto l = dynamic_cast<const LaplacianExpr*>(e)) {
    // Check if argument is psi
    if (auto v = dynamic_cast<const VariableExpr*>(l->arg.get())) {
        if (v->name == "psi")
            r.hasLaplacianPsi = true;
    }

    // continue scanning inside argument
    scanExpr(l->arg.get(), r);
    return;
}

    // -------------------------
    // Binary expression
    // -------------------------
    if (auto b = dynamic_cast<const BinaryExpr*>(e)) {
        scanExpr(b->lhs.get(), r);
        scanExpr(b->rhs.get(), r);
        return;
    }

    // NumberExpr → ignore
}

} // namespace

// ======================================================
// PUBLIC API
// ======================================================

SemanticInfo analyze(const Equation& eq)
{
    ScanResult r;
    scanExpr(eq.lhs.get(), r);
    scanExpr(eq.rhs.get(), r);

    SemanticInfo sem;
    
    // quantum
    if (r.hasPsi) {
        sem.type = PDEType::Quantum;
    }
    // hyperbolic = second order in time
    else if (r.hasTimeDerivative && r.maxTimeOrder >= 2) {
        sem.type = PDEType::Hyperbolic;
    }
    // parabolic = first order in time
    else if (r.hasTimeDerivative) {
        sem.type = PDEType::Parabolic;
    }
    // otherwise elliptic
    else {
        sem.type = PDEType::Elliptic;
    }
    return sem;
}

