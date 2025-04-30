/*! \file	    function.cpp
	\brief	    Function class definitions
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Definitions of the Function classes derived from Operation
  class

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

#include "../inc/function.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"
using namespace std;

namespace exprevaluator {
	void OneArgFunction::normalize(OperandStack& operand_stack) const {
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

	void TwoArgFunction::normalize(OperandStack& operand_stack) const {
		array<Operand::pointer_type, 2> operands;
		bool is_real{ false };
		unsigned num_of_bools{ 0 };
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

			if (is<Real>(operands[index]))
				is_real = true;
			else if (is<Boolean>(operands[index]))
				++num_of_bools;
		}

		if (num_of_bools == 1)
			throw runtime_error("Cannot convert");
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

	void ThreeArgFunction::normalize(OperandStack& operand_stack) const {
		array<Operand::pointer_type, 3> operands;
		array<string, 3> operand_names{ "Year", "Month", "Day" };
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
		}
		for (size_t i{ 0 }; i < operands.size(); ++i) {
			if (!is<Integer>(operands[i]))
				throw runtime_error(operand_names[i] + " parameter is not an integer");

			operand_stack.push(move(operands[i]));
		}
	}
}	// End of namespace exprevaluator