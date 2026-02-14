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
