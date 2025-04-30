/*! \file	    integer.cpp
	\brief	    Integer class definition
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Definition of the Integer classes derived from Operand class

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

#include "../inc/integer.hpp"
#include "../inc/boolean.hpp"
#include "../inc/real.hpp"
#include <functional>
using namespace std;

namespace exprevaluator {
	// Integer value
	[[nodiscard]] Integer::string_type Integer::str() const {
		Integer::string_type original{ value_.str() };
		Integer::string_type result;
		size_t count{ 0 };
		for (auto it{ rbegin(original) }; it != rend(original); ++it) {
			if (count == 3) {
				result.push_back(',');
				count = 0;
			}
			result.push_back(*it);
			++count;
		}
		reverse(begin(result), end(result));
		return result;
	}

	// 1. Unary operators
	DEFINE_OPERATION(Integer, perform_negation) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(-value_of<Integer>(operand)));
	}
	DEFINE_OPERATION(Integer, perform_not) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		auto value{ value_of<Integer>(operand) == 0 ? 1 : 0 };
		return convert<Operand>(make<Integer>(value));
	}
	DEFINE_OPERATION(Integer, perform_factorial) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		auto value{ value_of<Integer>(operand) };
		if (value < 0)
			throw runtime_error("Attempt to assign a negative value to an unsigned type.");

		auto result{ Integer::value_type(1) };
		for (auto i{ Integer::value_type(2) }; i <= value; ++i)
			result *= i;
		return convert<Operand>(make<Integer>(result));
	}

	// 2. Binary operators
	// - Arithmetic
	DEFINE_OPERATION(Integer, perform_addition) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(value_of<Integer>(lhs) + value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_subtraction) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(value_of<Integer>(lhs) - value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_multiplication) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(value_of<Integer>(lhs) * value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_division) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		if (value_of<Integer>(rhs) == 0)
			throw runtime_error("Integer Division by zero.");
		return convert<Operand>(make<Integer>(value_of<Integer>(lhs) / value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_modulus) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(value_of<Integer>(lhs) % value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_power) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		if (value_of<Integer>(rhs) < 0) {
			lhs = convert<Operand>(make<Real>(value_of<Integer>(lhs).convert_to<Real::value_type>()));
			rhs = convert<Operand>(make<Real>(value_of<Integer>(rhs).convert_to<Real::value_type>()));
			operand_stack.push(lhs);
			operand_stack.push(rhs);
			return operand_stack.top()->perform_power(operand_stack);
		}

		function<Integer::value_type(Integer::value_type, Integer::value_type)> fast_power{ [&](Integer::value_type base, Integer::value_type exponent) -> Integer::value_type {
			if (exponent.is_zero())
				return Integer::value_type(1);
			auto x{ fast_power(base, exponent / 2) };
			return x * x * (exponent % 2 == 0 ? 1 : base);
		} };

		return convert<Operand>(make<Integer>(fast_power(value_of<Integer>(lhs), value_of<Integer>(rhs))));
	}

	// - Relational
	DEFINE_OPERATION(Integer, perform_equality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Integer>(lhs) == value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_greater) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Integer>(lhs) > value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_greater_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Integer>(lhs) >= value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_inequality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Integer>(lhs) != value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_less) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Integer>(lhs) < value_of<Integer>(rhs)));
	}
	DEFINE_OPERATION(Integer, perform_less_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Integer>(lhs) <= value_of<Integer>(rhs)));
	}

	// 3. One-Argument Functions
	DEFINE_OPERATION(Integer, perform_abs) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(abs(value_of<Integer>(operand))));
	}
	DEFINE_OPERATION(Integer, perform_arccos) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(acos(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_arcsin) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(asin(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_arctan) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(atan(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_ceil) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(ceil(value_of<Integer>(operand).convert_to<Real::value_type>()).convert_to<Integer::value_type>()));
	}
	DEFINE_OPERATION(Integer, perform_cos) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(cos(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_exp) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(exp(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_floor) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(floor(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_lb) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log2(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_ln) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_log) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log10(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_sin) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(sin(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_sqrt) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(sqrt(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}
	DEFINE_OPERATION(Integer, perform_tan) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(tan(value_of<Integer>(operand).convert_to<Real::value_type>())));
	}

	// 4. Two-Argument Functions
	DEFINE_OPERATION(Integer, perform_arctan2) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		lhs = convert<Operand>(make<Real>(value_of<Integer>(lhs).convert_to<Real::value_type>()));
		rhs = convert<Operand>(make<Real>(value_of<Integer>(rhs).convert_to<Real::value_type>()));
		operand_stack.push(lhs);
		operand_stack.push(rhs);
		return operand_stack.top()->perform_arctan2(operand_stack);
	}
	DEFINE_OPERATION(Integer, perform_max) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(max(value_of<Integer>(lhs), value_of<Integer>(rhs))));
	}
	DEFINE_OPERATION(Integer, perform_min) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Integer>(min(value_of<Integer>(lhs), value_of<Integer>(rhs))));
	}
	DEFINE_OPERATION(Integer, perform_pow) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		if (value_of<Integer>(rhs) < 0) {
			lhs = convert<Operand>(make<Real>(value_of<Integer>(lhs).convert_to<Real::value_type>()));
			rhs = convert<Operand>(make<Real>(value_of<Integer>(rhs).convert_to<Real::value_type>()));
			operand_stack.push(lhs);
			operand_stack.push(rhs);
			return operand_stack.top()->perform_pow(operand_stack);
		}

		function<Integer::value_type(Integer::value_type, Integer::value_type)> fast_power{ [&](Integer::value_type base, Integer::value_type exponent) -> Integer::value_type {
			if (exponent.is_zero())
				return Integer::value_type(1);
			auto x{ fast_power(base, exponent / 2) };
			return x * x * (exponent % 2 == 0 ? 1 : base);
		} };

		return convert<Operand>(make<Integer>(fast_power(value_of<Integer>(lhs), value_of<Integer>(rhs))));
	}
}	// End of namespace exprevaluator