#pragma once
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>
#include "lexer/lexer.hpp"
#include "lexer/token.hpp" // 🟢 Uses TokenKind
#include "parser/ast.hpp"

class Parser {
public:
    explicit Parser(Lexer& lexer);
    
    // Entry point
    std::unique_ptr<System> parse();

private:
    Lexer& lexer;
    Token current;
    Token prev;

    // Parsing Rules
    std::unique_ptr<Equation> parseEquation();
    std::unique_ptr<Node> parseExpression();
    std::unique_ptr<Node> parseTerm();
    std::unique_ptr<Node> parseFactor();
    std::unique_ptr<Node> parsePrimary();
    std::unique_ptr<Node> parseUnary();
    // Helper Functions
    Token advance();
    
    // 🟢 FIX: These must use TokenKind, not TokenType
    bool check(TokenKind kind) const; 
    bool match(std::initializer_list<TokenKind> kinds);
    Token consume(TokenKind kind, std::string message);
    
    bool isAtEnd() const;
    Token previous() const;
    Token peek() const;
};
