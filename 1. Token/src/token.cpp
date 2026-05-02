/*! \file	    token.cpp
	\brief	    Token class definition and utilities
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

#include "../inc/token.hpp"
#include <typeinfo>
using namespace std;

namespace exprevaluator {
	[[nodiscard]] Token::string_type Token::str() const {
		return string_type("<") + string_type(typeid(*this).name()).substr(21) + string_type(">");
	}
}	// End of namespace exprevaluator