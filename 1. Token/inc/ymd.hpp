#pragma once
/*! \file	    ymd.hpp
	\brief	    Year, Month, and Day class declarations
	\author	    Khang Vu
	\date	    2025-04-28
	\copyright	Khang Vu

  =============================================================
  Declarations of the Year, Month, and Day classes derived from 
  Operand class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  Version 2025.04.30
	  Added Gregorian data type

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "operand.hpp"
#include "../../0. utilities/utilities.hpp"

namespace exprevaluator {
	// Year class
	class Year : public Operand {
	public:
		using value_type = detail::packaged_year_integer;
		DEF_POINTER_TYPE(Year)
	private:
		value_type	value_;
	public:
		Year(value_type value = value_type(0)) : value_{ value } {}

		[[nodiscard]] value_type	value() const { return value_; }
		[[nodiscard]] string_type	str() const override;
	};

	// Month class
	class Month : public Operand {
	public:
		using value_type = detail::packaged_month_integer;
		DEF_POINTER_TYPE(Month)
	private:
		value_type	value_;
	public:
		Month(value_type value = value_type(0)) : value_{ value } {}

		[[nodiscard]] value_type	value() const { return value_; }
		[[nodiscard]] string_type	str() const override;
	};

	// Day class
	class Day : public Operand {
	public:
		using value_type = detail::packaged_day;
		DEF_POINTER_TYPE(Day)
	private:
		value_type	value_;
	public:
		Day(value_type value = value_type(0)) : value_{ value } {}

		[[nodiscard]] value_type	value() const { return value_; }
		[[nodiscard]] string_type	str() const override;
	};
}	// End of namespace exprevaluator