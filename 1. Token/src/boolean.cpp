/*! \file	    boolean.cpp
	\brief	    Boolean class definitions
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Definitions of the Boolean classes derived from Operand class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */


#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/real.hpp"
using namespace std;

namespace exprevaluator {
	// Boolean value
	[[nodiscard]] Boolean::string_type Boolean::str() const {
		return value_ ? string_type("True") : string_type("False");
	}

	// 1. Unary operators
	DEFINE_OPERATION(Boolean, perform_not) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(!value_of<Boolean>(operand)));
	}

	// 2. Binary operators
	// - Arithmetic
	DEFINE_OPERATION(Boolean, perform_addition) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) + value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_multiplication) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) * value_of<Boolean>(rhs)));
	}

	// - Logical
	DEFINE_OPERATION(Boolean, perform_and) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) && value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_nand) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(!(value_of<Boolean>(lhs) && value_of<Boolean>(rhs))));
	}
	DEFINE_OPERATION(Boolean, perform_nor) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(!(value_of<Boolean>(lhs) || value_of<Boolean>(rhs))));
	}
	DEFINE_OPERATION(Boolean, perform_or) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) || value_of<Boolean>(rhs)));
	}

	// - Relational
	DEFINE_OPERATION(Boolean, perform_equality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) == value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_greater) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) > value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_greater_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) >= value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_inequality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) != value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_less) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) < value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_less_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) <= value_of<Boolean>(rhs)));
	}

	// - Bitwise
	DEFINE_OPERATION(Boolean, perform_xor) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Boolean>(lhs) ^ value_of<Boolean>(rhs)));
	}
	DEFINE_OPERATION(Boolean, perform_xnor) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(~(value_of<Boolean>(lhs) ^ value_of<Boolean>(rhs)) & 1));
	}

	// 3. One-Argument Functions
	DEFINE_OPERATION(Boolean, perform_abs) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(abs(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_arccos) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(acos(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_arcsin) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(asin(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_arctan) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(atan(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_ceil) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(ceil(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_cos) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(cos(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_exp) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(exp(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_floor) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(floor(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_lb) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log2(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_ln) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_log) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log10(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_sin) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(sin(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_sqrt) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(sqrt(value_of<Boolean>(operand))));
	}
	DEFINE_OPERATION(Boolean, perform_tan) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(tan(value_of<Boolean>(operand))));
	}

	// 4. Two-Argument Functions
	DEFINE_OPERATION(Boolean, perform_max) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(max(value_of<Boolean>(lhs), value_of<Boolean>(rhs))));
	}
	DEFINE_OPERATION(Boolean, perform_min) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(min(value_of<Boolean>(lhs), value_of<Boolean>(rhs))));
	}
}	// End of namespace exprevaluator