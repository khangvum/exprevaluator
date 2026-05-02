#pragma once
/*! \file	    parser.hpp
	\brief	    Parser class declaration
	\author	    Manh Khang Vu
	\date	    2025-01-06
	\copyright	Manh Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2026.05.01
	  Added Julian, Islamic, Hebrew, and Vulcan data types

  Version 2025.04.30
	  Added Gregorian data type

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Manh Khang Vu

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