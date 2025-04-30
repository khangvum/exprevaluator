/*! \file	    variable.cpp
	\brief	    Variable class definition
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Definition of the Variable classes derived from Operand class

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

#include "../inc/variable.hpp"
using namespace std;

namespace exprevaluator {
	[[nodiscard]] Variable::string_type Variable::str() const {
		if (!value_)
			return Variable::string_type("Variable: null");
		return value_->str();
	}
}	// End of namespace exprevaluator