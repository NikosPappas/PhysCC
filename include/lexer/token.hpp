#pragma once
#include <string>

enum class TokenKind{
	EndOfFile,
	Invalid,
	
	//--Literals--
	Number,
	Identifier,
	//--Operators--
	Plus,
	Minus,
	Star,
	Slash,
	Equal,
	Caret,
	//--Delimeters--
	LParen,
	RParen,
	LBracket,
	RBracket,
	Comma,
	//--Differential operators---
	D,
	Partial,
	Nabla,
	Lap,
	//--Quatnum
	Psi,
	I,
	Hbar,
	Ket,
	Bra,
	Arrow
};
struct Token{
       TokenKind kind;
       std::string lexeme;
       int line;
       int column;
};
