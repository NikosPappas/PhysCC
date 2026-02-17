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
#include "parser/parser.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

// --- Constructor ---
Parser::Parser(Lexer& lexer) 
    : lexer(lexer), 
      current{TokenKind::Invalid, "", 0, 0}, 
      prev{TokenKind::Invalid, "", 0, 0} 
{
    advance(); 
}

// --- Internal Helpers (The "Missing" References) ---

Token Parser::advance() {
    prev = current;
    while (true) {
        current = lexer.next();
        if (current.kind != TokenKind::Invalid) break;
        std::cerr << "Lexer Error: " << current.lexeme << " at line " << current.line << std::endl;
    }
    return prev;
}

Token Parser::consume(TokenKind kind, std::string message) {
    if (check(kind)) return advance();
    throw std::runtime_error(message + " (Found: " + current.lexeme + ")");
}

bool Parser::check(TokenKind kind) const {
    if (isAtEnd()) return false;
    return current.kind == kind;
}

bool Parser::match(std::initializer_list<TokenKind> kinds) {
    for (auto kind : kinds) {
        if (check(kind)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::isAtEnd() const {
    return current.kind == TokenKind::EndOfFile;
}

Token Parser::previous() const { return prev; }
Token Parser::peek() const { return current; }

// --- Core Parsing Logic ---

std::unique_ptr<System> Parser::parse() {
    auto system = std::make_unique<System>();
    while (!isAtEnd()) {
        system->equations.push_back(parseEquation());
    }
    return system;
}

std::unique_ptr<Equation> Parser::parseEquation() {
    std::string varName;
    
    // 1. Handle the prefix (i * hbar *)
    if (match({TokenKind::I})) {
        consume(TokenKind::Star, "Expect '*' after 'i'");
        if (match({TokenKind::Hbar})) {
            consume(TokenKind::Star, "Expect '*' after 'hbar'");
        }
    }

    // 2. Extract the Variable (Handling d/dt, ∂/∂t, or just the identifier)
    if (match({TokenKind::D, TokenKind::Partial})) {
        // It's a differential: consume the variable it's acting on
        if (match({TokenKind::Identifier, TokenKind::Psi})) {
            varName = previous().lexeme;
        } else {
            throw std::runtime_error("Expect variable after differential operator.");
        }
    } else if (match({TokenKind::Identifier, TokenKind::Psi})) {
        // It's a direct variable (the lexer might have already consumed 'dpsi' as 'psi')
        varName = previous().lexeme;
    } else {
        throw std::runtime_error("Expect variable name at start of equation.");
    }
    
    // 3. Handle the Denominator (/dt or /∂t)
    if (check(TokenKind::Slash)) {
        advance(); 
        if (match({TokenKind::D, TokenKind::Partial})) {
            consume(TokenKind::Identifier, "Expect 't' in denominator");
        } else {
            // Allow just 'dt' or 't'
            consume(TokenKind::Identifier, "Expect 'dt' or 't'");
        }
    }

    // 4. Match the Assignment
    consume(TokenKind::Equal, "Expect '=' after LHS of equation.");
    
    auto expr = parseExpression();
    return std::make_unique<Equation>(varName, std::move(expr));
}

std::unique_ptr<Node> Parser::parseExpression() {
    return parseTerm();
}

std::unique_ptr<Node> Parser::parseTerm() {
    auto expr = parseFactor();
    while (match({TokenKind::Plus, TokenKind::Minus})) {
        std::string op = previous().lexeme;
        auto right = parseFactor();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Node> Parser::parseFactor() {
    auto expr = parseUnary(); // 🟢 Changed from parsePrimary
    while (match({TokenKind::Star, TokenKind::Slash, TokenKind::Caret})) {
        std::string op = previous().lexeme;
        auto right = parseUnary(); // 🟢 Changed from parsePrimary
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Node> Parser::parsePrimary() {
    if (match({TokenKind::Number})) {
        return std::make_unique<Number>(std::stod(previous().lexeme));
    }
    
    if (match({TokenKind::Identifier, TokenKind::Psi, TokenKind::I, TokenKind::Hbar})) {
        std::string name = previous().lexeme;
        if (match({TokenKind::LParen})) { 
            std::vector<std::unique_ptr<Node>> args;
            if (!check(TokenKind::RParen)) {
                do {
                    args.push_back(parseExpression());
                } while (match({TokenKind::Comma}));
            }
            consume(TokenKind::RParen, "Expect ')'");
            return std::make_unique<CallExpr>(name, std::move(args));
        }
        return std::make_unique<Variable>(name);
    }
    
   if (match({TokenKind::Lap, TokenKind::Nabla})) {
        std::string name = "lap";
        if (previous().kind == TokenKind::Nabla && match({TokenKind::Caret})) {
            consume(TokenKind::Number, "Expect '2' after ∇^");
        }
        
        std::unique_ptr<Node> arg;
        // 🟢 FIX: Make parentheses optional
        if (match({TokenKind::LParen})) {
            arg = parseExpression();
            consume(TokenKind::RParen, "Expect ')'");
        } else {
            // Natural notation: ∇^2 psi (parse the next primary as the target)
            arg = parsePrimary(); 
        }
        
        std::vector<std::unique_ptr<Node>> args;
        args.push_back(std::move(arg));
        return std::make_unique<CallExpr>(name, std::move(args));
    }

    if (match({TokenKind::LParen})) {
        auto expr = parseExpression();
        consume(TokenKind::RParen, "Expect ')'");
        return expr;
    }
    
    throw std::runtime_error("Expect expression. Found: " + current.lexeme);
}
std::unique_ptr<Node> Parser::parseUnary() {
    if (match({TokenKind::Minus})) {
        std::string op = previous().lexeme;
        auto right = parseUnary(); // Recurse for --x
        // We can represent -x as (0 - x) in our AST or create a UnaryExpr node
        auto zero = std::make_unique<Number>(0.0);
        return std::make_unique<BinaryExpr>(std::move(zero), op, std::move(right));
    }
    return parsePrimary();
}
