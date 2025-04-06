#pragma once
/*! \file	    boolean.hpp
<<<<<<< HEAD
	\brief	    Boolean class declaration
=======
	\brief	    Boolean class declarations
>>>>>>> origin/master
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declarations of the Boolean classes derived from Operand 
  class, including the subclasses:
		
		class Boolean
			class True
			class False

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "operand.hpp"

<<<<<<< HEAD
namespace exprevaluator {
	// Boolean class
	class Boolean : public Operand {
	public:
		using value_type = bool;
		DEF_POINTER_TYPE(Boolean)
	private:
		value_type	value_;
	public:
		constexpr Boolean(const value_type& value) : value_{ value } {}

		[[nodiscard]] value_type	value() const { return value_; }
		[[nodiscard]] string_type	str() const override;

		// 1. Unary operators
		OVERRIDE_OPERATION(perform_not)

			// 2. Binary operators
			// - Arithmetic
			OVERRIDE_OPERATION(perform_addition)
			OVERRIDE_OPERATION(perform_multiplication)

			// - Logical
			OVERRIDE_OPERATION(perform_and)
			OVERRIDE_OPERATION(perform_nand)
			OVERRIDE_OPERATION(perform_nor)
			OVERRIDE_OPERATION(perform_or)

			// - Relational
			OVERRIDE_OPERATION(perform_equality)
			OVERRIDE_OPERATION(perform_greater)
			OVERRIDE_OPERATION(perform_greater_equal)
			OVERRIDE_OPERATION(perform_inequality)
			OVERRIDE_OPERATION(perform_less)
			OVERRIDE_OPERATION(perform_less_equal)

			// - Bitwise
			OVERRIDE_OPERATION(perform_xor)
			OVERRIDE_OPERATION(perform_xnor)

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
			OVERRIDE_OPERATION(perform_max)
			OVERRIDE_OPERATION(perform_min)
	};

	// Boolean True class
	class True : public Boolean {
	public:
		constexpr True() : Boolean{ true } {}
	};

	// Boolean False class
	class False : public Boolean {
	public:
		constexpr False() : Boolean{ false } {}
	};
};	// End of namespace exprevaluator`
=======
// Boolean class
class Boolean : public Operand {
public:
	using value_type = bool;
	DEF_POINTER_TYPE(Boolean)
private:
	value_type	value_;
public:
	constexpr Boolean(const value_type& value) : value_{ value } {}

	[[nodiscard]]	value_type	value() const { return value_; }
	[[nodiscard]]	string_type	str() const override;

	// 1. Unary operators
	OVERRIDE_OPERATION(perform_not)

	// 2. Binary operators
	// - Arithmetic
	OVERRIDE_OPERATION(perform_addition)
	OVERRIDE_OPERATION(perform_multiplication)

	// - Logical
	OVERRIDE_OPERATION(perform_and)
	OVERRIDE_OPERATION(perform_nand)
	OVERRIDE_OPERATION(perform_nor)
	OVERRIDE_OPERATION(perform_or)

	// - Relational
	OVERRIDE_OPERATION(perform_equality)
	OVERRIDE_OPERATION(perform_greater)
	OVERRIDE_OPERATION(perform_greater_equal)
	OVERRIDE_OPERATION(perform_inequality)
	OVERRIDE_OPERATION(perform_less)
	OVERRIDE_OPERATION(perform_less_equal)

	// - Bitwise
	OVERRIDE_OPERATION(perform_xor)
	OVERRIDE_OPERATION(perform_xnor)

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
	OVERRIDE_OPERATION(perform_max)
	OVERRIDE_OPERATION(perform_min)
};

// Boolean True class
class True : public Boolean {
public:
	constexpr True() : Boolean{ true } {}
};

// Boolean False class
class False : public Boolean {
public:
	constexpr False() : Boolean{ false } {}
};
>>>>>>> origin/master
