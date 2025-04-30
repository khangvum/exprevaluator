/*! \file	    operator.hpp
	\brief	    Operator class definitions
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Definitions of the Operator classes derived from Operation
  class

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

#include "../inc/operator.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/real.hpp"
#include "../inc/gregorian.hpp"
#include "../inc/variable.hpp"
#include "../inc/ymd.hpp"
#include <array>
#include <algorithm>
#include <stdexcept>
using namespace std;

namespace exprevaluator {
	void BinaryOperator::normalize(OperandStack& operand_stack) const {
		array<Operand::pointer_type, 2> operands;
		bool	is_real{ false },
                is_gregorian{ false };
		unsigned	num_of_bools{ 0 },
					num_of_gregorian{ 0 },
					num_of_ymd{ 0 };
		for (size_t i{ 0 }; i < operands.size(); ++i) {
			const size_t index{ operands.size() - 1 - i };
			operands[index] = operand_stack.top(); operand_stack.pop();

			// Get the values if the operand is Variable
			if (is<Variable>(operands[index])) {
				auto variable{ convert<Variable>(operands[index])->value() };
				if (!variable)
					throw runtime_error("Error: variable not initialized");

				operands[index] = variable;
			}

			if (is<Boolean>(operands[index]))
				++num_of_bools;
			else if (is<Real>(operands[index]))
				is_real = true;
			else if (is<Gregorian>(operands[index])) {
				is_gregorian = true;
				++num_of_gregorian;
			}
			else if (is<Year>(operands[index]) || is<Month>(operands[index]) || is<Day>(operands[index]))
				++num_of_ymd;
		}

		if (num_of_bools == 1 || num_of_ymd == 2 || (!is_gregorian && num_of_ymd == 1))
			throw runtime_error("Cannot convert");
		else if (is_gregorian && num_of_gregorian == 1) {
			Operand::pointer_type gregorian, ymd;
			for (size_t i{ 0 }; i < operands.size(); ++i) {
				if (is<Gregorian>(operands[i]))
					gregorian = move(operands[i]);
				else if (is<Year>(operands[i]) || is<Month>(operands[i]) || is<Day>(operands[i]) || is<Integer>(operands[i]))
					ymd = move(operands[i]);
			}

			if (!ymd)
				throw runtime_error("Operation cannot be performed on a Gregorian operand");

			operands = { ymd, gregorian };
		}
		else if (is_real) {
			for (size_t i{ 0 }; i < operands.size(); ++i) {
				if (is<Integer>(operands[i]))
					operands[i] = convert<Operand>(make<Real>(value_of<Integer>(operands[i]).convert_to<Real::value_type>()));
			}
		}

		for (size_t i{ 0 }; i < operands.size(); ++i) {
			operand_stack.push(move(operands[i]));
		}
	}

	void UnaryOperator::normalize(OperandStack& operand_stack) const {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		if (!is<Variable>(operand)) {
			operand_stack.push(operand);
			return;
		}

		auto variable{ convert<Variable>(operand)->value() };
		if (!variable)
			throw runtime_error("Error: variable not initialized");
		operand_stack.push(variable);
	}
}	// End of namespace exprevaluator