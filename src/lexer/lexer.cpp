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
#include "lexer/lexer.hpp"
#include <cwctype>

Lexer::Lexer(std::wistream& input)
    : in(input), current(L'\0'), line(1), column(0) {}

void Lexer::advance() {
    wchar_t c = in.get();
    if (!in) {
        current = L'\0';
        return;
    }
    current = c;
    if (current == L'\n') {
        line++;
        column = 0;
    } else {
        column++;
    }
}

// ⭐ FIX: Updated to handle comments
void Lexer::skipWhitespace() {
    while (true) {
        if (current == L' ' || current == L'\t' || current == L'\n' || current == L'\r') {
            advance();
        }
        else if (current == L'#') {
            // Comment: Skip until newline
            while (current != L'\n' && current != L'\0') {
                advance();
            }
        }
        else {
            break;
        }
    }
}

Token Lexer::make(TokenKind kind, const std::string& lexeme, int col) {
    return Token{kind, lexeme, line, col};
}

Token Lexer::lexNumber(int col) {
    std::string value;
    bool seenDot = false;
    while (std::iswdigit(current) || current == L'.') {
        if (current == L'.') {
            if (seenDot) break;
            seenDot = true;
        }
        value.push_back(static_cast<char>(current));
        advance();
    }
    return make(TokenKind::Number, value, col);
}

Token Lexer::lexIdentifier(int col) {
    std::string id;
    while (std::iswalnum(current) || current == L'_') {
        id.push_back(static_cast<char>(current));
        advance();
    }
    // Keywords
    if (id == "d")    return make(TokenKind::D, id, col);
    if (id == "lap")  return make(TokenKind::Lap, id, col);
    if (id == "i")    return make(TokenKind::I, id, col);
    if (id == "hbar") return make(TokenKind::Hbar, id, col);
    if (id == "psi")  return make(TokenKind::Psi, id, col);
    return make(TokenKind::Identifier, id, col);
}

Token Lexer::next() {
    if (current == L'\0') advance();
    skipWhitespace(); // ⭐ Now handles comments properly

    int startCol = column;

    if (current == L'\0') return make(TokenKind::EndOfFile, "", startCol);

    if (std::iswdigit(current)) return lexNumber(startCol);
    if ((current >= L'a' && current <= L'z') || (current >= L'A' && current <= L'Z') || current == L'_')
        return lexIdentifier(startCol);

    if (current == L'∂') { advance(); return make(TokenKind::Partial, "∂", startCol); }
    if (current == L'∇') { advance(); return make(TokenKind::Nabla, "∇", startCol); }
    if (current == L'⟨') { advance(); return make(TokenKind::Bra, "⟨", startCol); }
    if (current == L'|') { advance(); return make(TokenKind::Ket, "|", startCol); }
    if (current == L'→') { advance(); return make(TokenKind::Arrow, "→", startCol); }
    if (current == L'ψ') { advance(); return make(TokenKind::Psi, "psi", startCol); }

    switch (current) {
        case L'+': advance(); return make(TokenKind::Plus, "+", startCol);
        case L'-': advance(); return make(TokenKind::Minus, "-", startCol);
        case L'*': advance(); return make(TokenKind::Star, "*", startCol);
        case L'/': advance(); return make(TokenKind::Slash, "/", startCol);
        case L'=': advance(); return make(TokenKind::Equal, "=", startCol);
        case L'^': advance(); return make(TokenKind::Caret, "^", startCol);
        case L'(': advance(); return make(TokenKind::LParen, "(", startCol);
        case L')': advance(); return make(TokenKind::RParen, ")", startCol);
        case L'[': advance(); return make(TokenKind::LBracket, "[", startCol);
        case L']': advance(); return make(TokenKind::RBracket, "]", startCol);
        case L',': advance(); return make(TokenKind::Comma, ",", startCol);
    }

    wchar_t bad = current;
    advance();
    return make(TokenKind::Invalid, "<unicode>", startCol);
}
