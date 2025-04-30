#pragma once
/*! \file	    token.hpp
	\brief	    Token class declaration and utilities
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.04.30
	  Added Gregorian data type

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include <memory>
#include <string>
#include <vector>
#include <ostream>

namespace exprevaluator {
	// Define the type of smart pointer used in this program
#define DEF_POINTER_TYPE(_TT) using pointer_type = std::shared_ptr<_TT>;

	// Token base class
	class Token {
	public:
		DEF_POINTER_TYPE(Token)
			using string_type = std::string;
	private:
		// Block copy operator & constructor
		Token(const Token&) = delete;
		Token& operator = (const Token&) = delete;
	public:
		constexpr Token() = default;
		virtual ~Token() = default;

		/*	\brief		Get the string representation of the token
			\return		string_type - The string representation of the token
		*/
		[[nodiscard]] virtual string_type str() const;
	};

	/*	\brief		Make a new smart-pointer managed Token object
		\return		Token::pointer_type	- A pointer to the token
	*/
	template<typename T> [[nodiscard]] inline
		Token::pointer_type make() { return Token::pointer_type(new T); }

	/*	\brief		Make a new smart-pointer managed Token object with constructor parameter
		\param		const U& param		- The constructor parameter
		\return		Token::pointer_type	- A pointer to the token
	*/
	template<typename T, typename U> [[nodiscard]] inline
		Token::pointer_type make(const U& param) { return Token::pointer_type(new T(param)); }

	/*	\brief		Compare two tokens for same value
		\param		const Token::pointer_type& lhs	- The left-hand side token
					const Token::pointer_type& rhs	- The right-hand side token
		\return		bool							- The result of the comparison
	*/
	[[nodiscard]] inline
		bool operator == (const Token::pointer_type& lhs, const Token::pointer_type& rhs) {
		return lhs->str() == rhs->str();
	}

	/*	\brief		Test for family membership
		\param		const ORIGINAL_TYPE& token	- The token to test
		\return		bool						- The result of the test
	*/
	template<typename CAST_TYPE, typename ORIGINAL_TYPE> [[nodiscard]] inline
		bool is(const ORIGINAL_TYPE& token) {
		return dynamic_cast<const CAST_TYPE*>(token.get()) != nullptr;
	}

	template<typename CAST_TYPE, typename ORIGINAL_TYPE> [[nodiscard]] inline
		bool is(const ORIGINAL_TYPE* token_ptr) {
		return dynamic_cast<const CAST_TYPE*>(token_ptr) != nullptr;
	}

	/*	\brief		Convert to subclass type
		\param		const Token::pointer_type& token		- The token to convert
		\return		typename CONVERTED_TYPE::pointer_type	- The converted token
	*/
	template<typename CONVERTED_TYPE> [[nodiscard]] inline
		typename CONVERTED_TYPE::pointer_type convert(const Token::pointer_type& token) {
		return std::dynamic_pointer_cast<CONVERTED_TYPE>(token);
	}

	// Container for tokens
	using TokenList = std::vector<Token::pointer_type>;

	// Stream operators
	inline std::ostream& operator << (std::ostream& os, const Token& token) {
		return os << token.str();
	}

	inline std::ostream& operator << (std::ostream& os, const Token::pointer_type& token) {
		return os << token->str();
	}
}	// End of namespace exprevaluator