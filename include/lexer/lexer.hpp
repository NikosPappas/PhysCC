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
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "token.hpp" // Ensure this defines TokenKind and Token

class Lexer {
public:
    explicit Lexer(std::wistream& input);
    
    // The main function to get the next token
    Token next(); 

    // Helper to get all tokens at once (for debugging/testing)
    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (true) {
            Token t = next();
            tokens.push_back(t);
            if (t.kind == TokenKind::EndOfFile) break;
        }
        return tokens;
    }

private:
    std::wistream& in;
    wchar_t current;
    int line;
    int column;

    void advance();
    void skipWhitespace();
    
    Token make(TokenKind kind, const std::string& lexeme, int col);
    Token lexNumber(int col);
    Token lexIdentifier(int col);
};
