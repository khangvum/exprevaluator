#pragma once
/*! \file	    integer.hpp
	\brief	    Integer class declaration
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declaration of the Integer classes derived from Operand class

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
#include <boost/multiprecision/cpp_int.hpp>

namespace exprevaluator {
	// Integer class
	class Integer : public Operand {
	public:
		using value_type = boost::multiprecision::cpp_int;
		DEF_POINTER_TYPE(Integer)
	private:
		value_type	value_;
	public:
		Integer(value_type value = value_type(0)) : value_{ value } {}

		[[nodiscard]] value_type	value() const { return value_; }
		[[nodiscard]] string_type	str() const override;

		// 1. Unary operators
		OVERRIDE_OPERATION(perform_negation)
		OVERRIDE_OPERATION(perform_not)
		OVERRIDE_OPERATION(perform_factorial)

		// 2. Binary operators
		// - Arithmetic
		OVERRIDE_OPERATION(perform_addition)
		OVERRIDE_OPERATION(perform_subtraction)
		OVERRIDE_OPERATION(perform_multiplication)
		OVERRIDE_OPERATION(perform_division)
		OVERRIDE_OPERATION(perform_modulus)
		OVERRIDE_OPERATION(perform_power)

		// - Relational
		OVERRIDE_OPERATION(perform_equality)
		OVERRIDE_OPERATION(perform_greater)
		OVERRIDE_OPERATION(perform_greater_equal)
		OVERRIDE_OPERATION(perform_inequality)
		OVERRIDE_OPERATION(perform_less)
		OVERRIDE_OPERATION(perform_less_equal)

		// 3. One-Argument Functions
		OVERRIDE_OPERATION(perform_abs)
		OVERRIDE_OPERATION(perform_arccos)
		OVERRIDE_OPERATION(perform_arcsin)
		OVERRIDE_OPERATION(perform_arctan)
		OVERRIDE_OPERATION(perform_ceil)
		OVERRIDE_OPERATION(perform_cos)
		OVERRIDE_OPERATION(perform_exp)
		OVERRIDE_OPERATION(perform_floor)
		OVERRIDE_OPERATION(perform_lb)
		OVERRIDE_OPERATION(perform_ln)
		OVERRIDE_OPERATION(perform_log)
		OVERRIDE_OPERATION(perform_sin)
		OVERRIDE_OPERATION(perform_sqrt)
		OVERRIDE_OPERATION(perform_tan)

		// 4. Two-Argument Functions
		OVERRIDE_OPERATION(perform_arctan2)
		OVERRIDE_OPERATION(perform_max)
		OVERRIDE_OPERATION(perform_min)
		OVERRIDE_OPERATION(perform_pow)
	};
}	// End of namespace exprevaluator