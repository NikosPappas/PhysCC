/*
 * PhysCC - Domain-Specific Compiler for Physics Simulations
 * Copyright (C) 2026  [Το Όνομά Σας]
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

// Helper to consume tokens
Token Parser::consume(TokenType type, std::string message) {
    if (check(type)) return advance();
    throw std::runtime_error(message);
}

std::unique_ptr<System> Parser::parse() {
    auto system = std::make_unique<System>();
    while (!isAtEnd()) {
        // 🟢 FIX: Use push_back, not add()
        system->equations.push_back(parseEquation());
    }
    return system;
}

std::unique_ptr<Equation> Parser::parseEquation() {
    consume(TokenType::IDENTIFIER, "Expect variable name.");
    std::string varName = previous().lexeme;
    
    // Handle "du/dt" syntax roughly
    if (check(TokenType::SLASH)) {
        advance(); 
        consume(TokenType::IDENTIFIER, "Expect 'dt'"); 
        if (varName.size() > 1 && varName[0] == 'd') varName = varName.substr(1);
    }

    consume(TokenType::EQUAL, "Expect '=' after variable.");
    auto expr = parseExpression();
    
    return std::make_unique<Equation>(varName, std::move(expr));
}

std::unique_ptr<Node> Parser::parseExpression() {
    return parseTerm();
}

std::unique_ptr<Node> Parser::parseTerm() {
    auto expr = parseFactor();
    while (match({TokenType::PLUS, TokenType::MINUS})) {
        std::string op = previous().lexeme;
        auto right = parseFactor();
        // 🟢 FIX: Use BinaryExpr instead of BinaryOpNode
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Node> Parser::parseFactor() {
    auto expr = parsePrimary();
    while (match({TokenType::STAR, TokenType::SLASH})) {
        std::string op = previous().lexeme;
        auto right = parsePrimary();
        // 🟢 FIX: Use BinaryExpr
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Node> Parser::parsePrimary() {
    if (match({TokenType::NUMBER})) {
        // 🟢 FIX: Use Number instead of NumberNode
        return std::make_unique<Number>(std::stod(previous().lexeme));
    }
    if (match({TokenType::IDENTIFIER})) {
        std::string name = previous().lexeme;
        if (check(TokenType::LEFT_PAREN)) { 
            // Function call logic
            consume(TokenType::LEFT_PAREN, "Expect '('");
            std::vector<std::unique_ptr<Node>> args;
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    args.push_back(parseExpression());
                } while (match({TokenType::COMMA}));
            }
            consume(TokenType::RIGHT_PAREN, "Expect ')'");
            // 🟢 FIX: Use CallExpr
            return std::make_unique<CallExpr>(name, std::move(args));
        }
        // 🟢 FIX: Use Variable instead of VariableNode
        return std::make_unique<Variable>(name);
    }
    if (match({TokenType::LEFT_PAREN})) {
        auto expr = parseExpression();
        consume(TokenType::RIGHT_PAREN, "Expect ')'");
        return expr;
    }
    throw std::runtime_error("Expect expression.");
}
