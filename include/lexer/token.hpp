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
