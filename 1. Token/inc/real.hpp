#pragma once
/*! \file	    real.hpp
	\brief	    Real class declarations
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declarations of the Real classes derived from Operand class,
  including the subclasses:

		class Real
			class Pi
			class 

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */


#include "operand.hpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>

// Real class
class Real : public Operand {
public:
	using value_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1000, int32_t, void>>;
	DEF_POINTER_TYPE(Real)
private:
	value_type	value_;
public:
	Real(value_type value = value_type(0.0)) : value_{ value } {}
	[[nodiscard]] value_type	value() const { return value_; }
	[[nodiscard]] string_type	str() const override;

	// 1. Unary operators
	OVERRIDE_OPERATION(perform_negation)
	OVERRIDE_OPERATION(perform_not)

	// 2. Binary operators
	// - Arithmetic
	OVERRIDE_OPERATION(perform_addition)
	OVERRIDE_OPERATION(perform_subtraction)
	OVERRIDE_OPERATION(perform_multiplication)
	OVERRIDE_OPERATION(perform_division)
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

// Pi constant class
class Pi : public Real {
public:
	Pi() : Real(boost::math::constants::pi<value_type>()) {}
};

// E (Euler) constant class
class E : public Real {
public:
	E() : Real(boost::math::constants::e<value_type>()) {}
};