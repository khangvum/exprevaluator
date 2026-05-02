#pragma once
/*! \file	    calendar.hpp
	\brief	    Calendar class declaration
    \author	    Manh Khang Vu
    \date	    2026-04-27
    \copyright	Manh Khang Vu

  =============================================================
  Declaration of the Calendar classes derived from Operand 
  class
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

#include "operand.hpp"

namespace exprevaluator {
	// Calendar base class
    class Calendar : public Operand {
    public:
        using value_type = jd_t;
        DEF_POINTER_TYPE(Calendar)

        [[nodiscard]] virtual value_type	value() const = 0;
        [[nodiscard]] string_type           str() const override = 0;
    };

	// User-defined literals
	// - Convert a Gregorian year AD to an astronomical Gregorian year
	constexpr year_t operator ""_AD(unsigned long long gregorian_year_AD) {
		return static_cast<year_t>(gregorian_year_AD);
	}
	constexpr year_t operator ""_ad(unsigned long long gregorian_year_AD) {
		return static_cast<year_t>(gregorian_year_AD);
	}

	// - Convert a Gregorian year BC to an astronomical Gregorian year
	constexpr year_t operator ""_BC(unsigned long long gregorian_year_BC) {
		return -static_cast<year_t>(gregorian_year_BC) + 1;
	}
	constexpr year_t operator ""_bc(unsigned long long gregorian_year_BC) {
		return -static_cast<year_t>(gregorian_year_BC) + 1;
	}
}   // End of namespace exprevaluator