/*! \file	    tokenizer.cpp
	\brief	    Tokenizer class definition
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "../inc/tokenizer.hpp"
#include "../../1. Token/inc/boolean.hpp"
#include "../../1. Token/inc/real.hpp"
#include "../../1. Token/inc/function.hpp"
#include "../../1. Token/inc/operator.hpp"
#include "../../1. Token/inc/pseudo_operation.hpp"

#include <cassert>
using namespace std;

// Default constructor loads the keyword dictionary
Tokenizer::Tokenizer() {
	keywords_["abs"]	 = keywords_["Abs"]		= keywords_["ABS"]		= make<Abs>();
	keywords_["and"]	 = keywords_["And"]		= keywords_["AND"]		= make<And>();
	keywords_["arccos"]  = keywords_["Arccos"]	= keywords_["ARCCOS"]	= make<Arccos>();
	keywords_["arcsin"]  = keywords_["Arcsin"]	= keywords_["ARCSIN"]	= make<Arcsin>();
	keywords_["arctan"]  = keywords_["Arctan"]	= keywords_["ARCTAN"]	= make<Arctan>();
	keywords_["arctan2"] = keywords_["Arctan2"] = keywords_["ARCTAN2"]	= make<Arctan2>();
	keywords_["ceil"]	 = keywords_["Ceil"]	= keywords_["CEIL"]		= make<Ceil>();
	keywords_["cos"]	 = keywords_["Cos"]		= keywords_["COS"]		= make<Cos>();
	keywords_["e"]		 = keywords_["E"]								= make<E>();
	keywords_["exp"]	 = keywords_["Exp"]		= keywords_["EXP"]		= make<Exp>();
	keywords_["false"]	 = keywords_["False"]	= keywords_["FALSE"]	= make<False>();
	keywords_["floor"]	 = keywords_["Floor"]	= keywords_["FLOOR"]	= make<Floor>();
	keywords_["lb"]		 = keywords_["Lb"]		= keywords_["LB"]		= make<Lb>();
	keywords_["ln"]		 = keywords_["Ln"]		= keywords_["LN"]		= make<Ln>();
	keywords_["log"]	 = keywords_["Log"]		= keywords_["LOG"]		= make<Log>();
	keywords_["max"]	 = keywords_["Max"]		= keywords_["MAX"]		= make<Max>();
	keywords_["min"]	 = keywords_["Min"]		= keywords_["MIN"]		= make<Min>();
	keywords_["mod"]	 = keywords_["Mod"]		= keywords_["MOD"]		= make<Modulus>();
	keywords_["nand"]	 = keywords_["Nand"]	= keywords_["NAND"]		= make<Nand>();
	keywords_["nor"]	 = keywords_["Nor"]		= keywords_["NOR"]		= make<Nor>();
	keywords_["not"]	 = keywords_["Not"]		= keywords_["NOT"]		= make<Not>();
	keywords_["or"]		 = keywords_["Or"]		= keywords_["OR"]		= make<Or>();
	keywords_["pi"]		 = keywords_["Pi"]		= keywords_["PI"]		= make<Pi>();
	keywords_["pow"]	 = keywords_["Pow"]		= keywords_["POW"]		= make<Pow>();
	keywords_["result"]  = keywords_["Result"]	= keywords_["RESULT"]	= make<Result>();
	keywords_["sin"]	 = keywords_["Sin"]		= keywords_["SIN"]		= make<Sin>();
	keywords_["sqrt"]	 = keywords_["Sqrt"]	= keywords_["SQRT"]		= make<Sqrt>();
	keywords_["tan"]	 = keywords_["Tan"]		= keywords_["TAN"]		= make<Tan>();
	keywords_["true"]	 = keywords_["True"]	= keywords_["TRUE"]		= make<True>();
	keywords_["xnor"]	 = keywords_["Xnor"]	= keywords_["XNOR"]		= make<Xnor>();
	keywords_["xor"]	 = keywords_["Xor"]		= keywords_["XOR"]		= make<Xor>();
}

// Get an identifier from the expression string
// Assumes that the current_char is pointing to a alphabetic
[[nodiscard]] Token::pointer_type Tokenizer::_get_identifier(Tokenizer::string_type::const_iterator& current_char, const Tokenizer::string_type& expression) {
	// Accumulate identifier
	string_type identifier;
	do
		identifier += *current_char++;
	while (current_char != end(expression) && isalnum(*current_char));

	// Check for predefined identifiers
	dictionary_type::iterator it{ keywords_.find(identifier) };
	if (it != end(keywords_))
		return it->second;

	// Check for variables
	it = variables_.find(identifier);
	if (it != end(variables_))
		return it->second;

	// Add a variable
	Token::pointer_type result{ make<Variable>() };
	variables_[identifier] = result;
	return result;
}

// Get a number token from the expression string
[[nodiscard]] Token::pointer_type Tokenizer::_get_number(Tokenizer::string_type::const_iterator& current_char, const Tokenizer::string_type& expression) {
	assert(isdigit(*current_char) && "current_char must point to a digit.");

	// Either an Integer or Real
	string_type digits(1, *current_char++);

	while (current_char != end(expression) && isdigit(*current_char))
		digits += *current_char++;

	if (current_char == end(expression) || (!isdigit(*current_char) && *current_char != '.'))
		return make<Integer>(Integer::value_type(digits));

	// Real number
	digits += *current_char++;
	while (current_char != end(expression) && isdigit(*current_char))
		digits += *current_char++;

	return make<Real>(Real::value_type(digits));
}

// Tokenize the expression string
TokenList Tokenizer::tokenize(const string_type& expression) {
	TokenList tokenized_expression;
	auto current_char{ cbegin(expression) };

	while (1) {
		// Trim whitespace
		while (current_char != end(expression) && isspace(*current_char))
			++current_char;

		// Check for end of expression
		if (current_char == end(expression))
			break;

		// Check for a number
		if (isdigit(*current_char)) {
			tokenized_expression.push_back(_get_number(current_char, expression));
			continue;
		}

		// Check for two-character operators
#define CHECK_2OP(symbol1, symbol2, token)\
		if (*current_char ==  symbol1) {\
			auto next_char{ next(current_char) };\
			if (next_char != end(expression) && *next_char == symbol2) {\
				current_char = next(next_char);\
				tokenized_expression.push_back(make<token>());\
				continue;\
			}\
		}
		CHECK_2OP('<', '=', LessEqual)
		CHECK_2OP('>', '=', GreaterEqual)
		CHECK_2OP('=', '=', Equality)
		CHECK_2OP('!', '=', Inequality)
		CHECK_2OP('*', '*', Power)
#undef CHECK_2OP

		// Check for one-character operators
#define CHECK_OP(symbol, token)\
		if (*current_char == symbol) {\
			++current_char;\
			tokenized_expression.push_back(make<token>());\
			continue;\
		}
		CHECK_OP('*', Multiplication)
		CHECK_OP('/', Division)
		CHECK_OP('%', Modulus)
		CHECK_OP('(', LeftParenthesis)
		CHECK_OP(')', RightParenthesis)
		CHECK_OP(',', ArgumentSeparator)
		CHECK_OP('<', Less)
		CHECK_OP('>', Greater)
		CHECK_OP('!', Factorial)
		CHECK_OP('=', Assignment)
#undef CHECK_OP

		// Check for multii-purpose operators
		if (*current_char == '+') {
			++current_char;
			if (!tokenized_expression.empty()  &&
				(is<RightParenthesis>(tokenized_expression.back()) ||
					is<Operand>(tokenized_expression.back()) ||
					is<PostfixOperator>(tokenized_expression.back())))
				tokenized_expression.push_back(make<Addition>());
			else
				tokenized_expression.push_back(make<Identity>());
			continue;
		}

		if (*current_char == '-') {
			++current_char;
			if (!tokenized_expression.empty() &&
				(is<RightParenthesis>(tokenized_expression.back()) ||
					is<Operand>(tokenized_expression.back()) ||
					is<PostfixOperator>(tokenized_expression.back())))
				tokenized_expression.push_back(make<Subtraction>());
			else
				tokenized_expression.push_back(make<Negation>());
			continue;
		}

		// Check for identifiers
		if (isalpha(*current_char)) {
			tokenized_expression.push_back(_get_identifier(current_char, expression));
			continue;
		}

		// Not a recognized token
		throw XBadCharacter(expression, current_char - begin(expression));

	}

	return tokenized_expression;
}