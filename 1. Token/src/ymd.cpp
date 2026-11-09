/*! \file	    ymd.cpp
	\brief	    Year, Month, and Day class definitions
	\author	    Manh Khang Vu
	\date	    2025-04-28
	\copyright	Manh Khang Vu

  =============================================================
  Definitions of the Year, Month, and Day classes derived from
  Operand class

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

#include "../inc/ymd.hpp"
#include "../inc/gregorian.hpp"
#include <format>
using namespace std;

namespace exprevaluator {
	// Year value
	[[nodiscard]] Year::string_type Year::str() const {
		return std::format("{} year{}", value_.years_, value_.years_ == 1 ? "" : "s");
	}

	// Month value
	[[nodiscard]] Month::string_type Month::str() const {
		return std::format("{} month{}", value_.months_, value_.months_ == 1 ? "" : "s");
	}

	// Day value
	[[nodiscard]] Day::string_type Day::str() const {
		return std::format("{} day{}", value_.days_, value_.days_ == 1 ? "" : "s");
	}
}	// End of namespace exprevaluator