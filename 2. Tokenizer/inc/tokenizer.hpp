#pragma once
/*! \file	    tokenizer.hpp
	\brief	    Tokenizer class declaration
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

#include "../../1. Token/inc/token.hpp"
#include <exception>
#include <map>

namespace exprevaluator {
	// Tokenizer class
	// - Used to create lists of tokens from expression strings
	// - Maintains a dictionary of variable toekns introduced by the expression strings
	class Tokenizer {
		// Block copy operator & constructor
		Tokenizer(const Tokenizer&) = delete;
		Tokenizer& operator = (const Tokenizer&) = delete;

		// === 1. Types ================================================
	public:
		using string_type = Token::string_type;

		// XTokenizer (Tokenizer Exception) class
		class XTokenizer : public std::exception {
			string_type expression_;
			size_t		location_;
		public:
			XTokenizer(const string_type& expression, size_t location, const char* msg)
				: std::exception{ msg }
				, expression_{ expression }
				, location_{ location }
			{}

			// Get the expresison string containing the bad character
			[[nodiscard]] constexpr string_type expression() const { return expression_; }

			// Get the location of the bad character in the expression string
			[[nodiscard]] constexpr size_t location() const { return location_; }
		};

		// XBadCharacter (Bad Character Exception) class
		struct XBadCharacter : public XTokenizer {
			XBadCharacter(const string_type& expression, size_t location)
				: XTokenizer(expression, location, "Tokenizer::Bad character in expression.") {
			}
		};

		// XNumericOverflow (Numeric Overflow Exception) class
		struct XNumericOverflow : public XTokenizer {
			XNumericOverflow(const string_type& expression, size_t location)
				: XTokenizer(expression, location, "Tokenizer::Too many digits in number.") {
			}
		};
	private:
		using dictionary_type = std::map<string_type, Token::pointer_type>;

		// === 2. Attributes ===========================================
	private:
		dictionary_type keywords_;
		dictionary_type variables_;

		// === 2. Operations ===========================================
	public:
		Tokenizer();

		/*	\brief		Tokenize an expression string
			\param		const string_type& expression	- The expression string
			\return		TokenList						- A list of tokens
			\note		Tokenizer dictionary may be updated if the expression contains variables
						Will throw XBadCharacter (Bad Character Exception) if the expression contains an un-tokenizable chracter
		*/
		TokenList tokenize(const string_type& expression);
	private:
		/*	\brief		Get an identifier token from the expression string
			\param		Tokenizer::string_type::const_iterator&	- Current character in the expression string
						const string_type& expression			- The expression string
			\return		Token::pointer_type						- A pointer to the token
		*/
		[[nodiscard]] Token::pointer_type _get_identifier(Tokenizer::string_type::const_iterator& current_char, const Tokenizer::string_type& expression);

		/*	\brief		Get a number token from the expression string
			\param		Tokenizer::string_type::const_iterator&	- Current character in the expression string
						const string_type& expression			- The expression string
			\return		Token::pointer_type						- A pointer to the token
		*/
		[[nodiscard]] Token::pointer_type _get_number(Tokenizer::string_type::const_iterator& current_char, const Tokenizer::string_type& expression);
	};
}	// End of namespace exprevaluator