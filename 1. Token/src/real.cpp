/*! \file	    real.cpp
	\brief	    Real class definitions
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Definitions of the Real classes derived from Operand class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */


#include "../inc/real.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

<<<<<<< HEAD
namespace exprevaluator {
	// Real value
	[[nodiscard]] Real::string_type Real::str() const {
		ostringstream oss;
		oss << fixed << setprecision(numeric_limits<value_type>::digits10) << value_;

		Integer::pointer_type integral_part{ convert<Integer>(make<Integer>(value_.convert_to<Integer::value_type>())) };
		size_t decimal_pos{ oss.str().find('.') };
		Real::string_type fractional_part{ oss.str().substr(decimal_pos) };

		// Trim the trailing zeros from the fractional part
		size_t end_pos{ fractional_part.find_last_not_of('0') };
		if (end_pos != Real::string_type::npos) {
			if (fractional_part[end_pos] == '.') {
				end_pos--; // Remove the dot if it's the last character
			}
			fractional_part = fractional_part.substr(0, end_pos + 1);
		}

		oss.str("");
		oss.clear();
		oss << integral_part->str() << fractional_part;
		return oss.str();
	}

	// 1. Unary operators
	DEFINE_OPERATION(Real, perform_negation) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(-value_of<Real>(operand)));
	}
	DEFINE_OPERATION(Real, perform_not) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		auto value{ value_of<Real>(operand) == 0.0 ? 1.0 : 0.0 };
		return convert<Operand>(make<Real>(value));
	}

	// 2. Binary operators
	// - Arithmetic
	DEFINE_OPERATION(Real, perform_addition) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(value_of<Real>(lhs) + value_of<Real>(rhs)));
	}

	DEFINE_OPERATION(Real, perform_subtraction) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(value_of<Real>(lhs) - value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_multiplication) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(value_of<Real>(lhs) * value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_division) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(value_of<Real>(lhs) / value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_power) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(pow(value_of<Real>(lhs), value_of<Real>(rhs))));
	}

	// - Relational
	DEFINE_OPERATION(Real, perform_equality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Real>(lhs) == value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_greater) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Real>(lhs) > value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_greater_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Real>(lhs) >= value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_inequality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Real>(lhs) != value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_less) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Real>(lhs) < value_of<Real>(rhs)));
	}
	DEFINE_OPERATION(Real, perform_less_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Real>(lhs) <= value_of<Real>(rhs)));
	}

	// 3. One-Argument Functions
	DEFINE_OPERATION(Real, perform_abs) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(abs(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_arccos) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(acos(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_arcsin) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(asin(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_arctan) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(atan(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_ceil) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(ceil(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_cos) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(cos(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_exp) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(exp(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_floor) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(floor(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_lb) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log2(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_ln) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_log) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(log10(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_sin) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(sin(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_sqrt) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(sqrt(value_of<Real>(operand))));
	}
	DEFINE_OPERATION(Real, perform_tan) {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(tan(value_of<Real>(operand))));
	}

	// 4. Two-Argument Functions
	DEFINE_OPERATION(Real, perform_arctan2) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(atan2(value_of<Real>(lhs), value_of<Real>(rhs))));
	}
	DEFINE_OPERATION(Real, perform_max) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(max(value_of<Real>(lhs), value_of<Real>(rhs))));
	}
	DEFINE_OPERATION(Real, perform_min) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(min(value_of<Real>(lhs), value_of<Real>(rhs))));
	}
	DEFINE_OPERATION(Real, perform_pow) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Real>(pow(value_of<Real>(lhs), value_of<Real>(rhs))));
	}
}	// End of namespace exprevaluator
=======
// Real value
[[nodiscard]] Real::string_type Real::str() const {
	ostringstream oss;
	oss << fixed << setprecision(numeric_limits<value_type>::digits10) << value_;

	Integer::pointer_type integral_part{ convert<Integer>(make<Integer>(value_.convert_to<Integer::value_type>())) };
	size_t decimal_pos{ oss.str().find('.') };
	Real::string_type fractional_part{ oss.str().substr(decimal_pos) };

	// Trim the trailing zeros from the fractional part
	size_t end_pos{ fractional_part.find_last_not_of('0') };
	if (end_pos != Real::string_type::npos) {
		if (fractional_part[end_pos] == '.') {
			end_pos--; // Remove the dot if it's the last character
		}
		fractional_part = fractional_part.substr(0, end_pos + 1);
	}

	oss.str("");
	oss.clear();
	oss << integral_part->str() << fractional_part;
	return oss.str();
}

// 1. Unary operators
DEFINE_OPERATION(Real, perform_negation) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(-value_of<Real>(operand)));
}
DEFINE_OPERATION(Real, perform_not) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	auto value{ value_of<Real>(operand) == 0.0 ? 1.0 : 0.0 };
	return convert<Operand>(make<Real>(value));
}

// 2. Binary operators
// - Arithmetic
DEFINE_OPERATION(Real, perform_addition) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(value_of<Real>(lhs) + value_of<Real>(rhs)));
}

DEFINE_OPERATION(Real, perform_subtraction) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(value_of<Real>(lhs) - value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_multiplication) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(value_of<Real>(lhs) * value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_division) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(value_of<Real>(lhs) / value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_power) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(pow(value_of<Real>(lhs), value_of<Real>(rhs))));
}

// - Relational
DEFINE_OPERATION(Real, perform_equality) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Boolean>(value_of<Real>(lhs) == value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_greater) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Boolean>(value_of<Real>(lhs) > value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_greater_equal) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Boolean>(value_of<Real>(lhs) >= value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_inequality) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Boolean>(value_of<Real>(lhs) != value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_less) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Boolean>(value_of<Real>(lhs) < value_of<Real>(rhs)));
}
DEFINE_OPERATION(Real, perform_less_equal) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Boolean>(value_of<Real>(lhs) <= value_of<Real>(rhs)));
}

// 3. One-Argument Functions
DEFINE_OPERATION(Real, perform_abs) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(abs(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_arccos) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(acos(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_arcsin) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(asin(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_arctan) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(atan(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_ceil) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(ceil(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_cos) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(cos(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_exp) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(exp(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_floor) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(floor(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_lb) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(log2(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_ln) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(log(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_log) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(log10(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_sin) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(sin(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_sqrt) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(sqrt(value_of<Real>(operand))));
}
DEFINE_OPERATION(Real, perform_tan) {
	auto operand{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(tan(value_of<Real>(operand))));
}

// 4. Two-Argument Functions
DEFINE_OPERATION(Real, perform_arctan2) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(atan2(value_of<Real>(lhs), value_of<Real>(rhs))));
}
DEFINE_OPERATION(Real, perform_max) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(max(value_of<Real>(lhs), value_of<Real>(rhs))));
}
DEFINE_OPERATION(Real, perform_min) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(min(value_of<Real>(lhs), value_of<Real>(rhs))));
}
DEFINE_OPERATION(Real, perform_pow) {
	auto rhs{ operand_stack.top() }; operand_stack.pop();
	auto lhs{ operand_stack.top() }; operand_stack.pop();
	return convert<Operand>(make<Real>(pow(value_of<Real>(lhs), value_of<Real>(rhs))));
}
>>>>>>> origin/master
