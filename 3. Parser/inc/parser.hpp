#pragma once
/*! \file	    parser.hpp
	\brief	    Parser class declaration
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

#include "../../1. Token/inc/token.hpp"

namespace exprevaluator {
	class Parser {
		// Block copy operator & constructor
		Parser(const Parser&) = delete;
		Parser& operator = (const Parser&) = delete;
	public:
		constexpr Parser() = default;

		/*	\brief		Parse the infix token list into a postfix token list
			\param		const TokenList&	- The infix token list
			\return		TokenList			- The postfix token list
		*/
		[[nodiscard]] TokenList parse(const TokenList& infix_tokens);
	};
}	// End of namespace exprevaluator