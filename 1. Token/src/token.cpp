/*! \file	    token.cpp
	\brief	    Token class definition and utilities
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

#include "../inc/token.hpp"
#include <typeinfo>
using namespace std;

<<<<<<< HEAD
namespace exprevaluator {
	[[nodiscard]] Token::string_type Token::str() const {
		return string_type("<") + string_type(typeid(*this).name()).substr(6) + string_type(">");
	}
}	// End of namespace exprevaluator
=======
[[nodiscard]] Token::string_type Token::str() const {
	return string_type("<") + string_type(typeid(*this).name()).substr(6) + string_type(">");
}
>>>>>>> origin/master
