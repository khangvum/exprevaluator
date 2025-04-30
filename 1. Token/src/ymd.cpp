/*! \file	    ymd.cpp
	\brief	    Year, Month, and Day class definitions
	\author	    Khang Vu
	\date	    2025-04-28
	\copyright	Khang Vu

  =============================================================
  Definitions of the Year, Month, and Day classes derived from
  Operand class

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

#include "../inc/ymd.hpp"
#include "../inc/gregorian.hpp"
#include <sstream>
using namespace std;

namespace exprevaluator {
	// Year value
	[[nodiscard]] Year::string_type Year::str() const {
		ostringstream oss;
		oss << value_.years_ << " year" << (value_.years_ == 1 ? "" : "s");
		return oss.str();
	}

	// Month value
	[[nodiscard]] Month::string_type Month::str() const {
		ostringstream oss;
		oss << value_.months_ << " month" << (value_.months_ == 1 ? "" : "s");
		return oss.str();
	}

	// Day value
	[[nodiscard]] Day::string_type Day::str() const {
		ostringstream oss;
		oss << value_.days_ << " day" << (value_.days_ == 1 ? "" : "s");
		return oss.str();
	}
}	// End of namespace exprevaluator