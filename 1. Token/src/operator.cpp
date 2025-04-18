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

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "../inc/operator.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"
#include <array>
#include <stdexcept>
using namespace std;

namespace exprevaluator {
	void BinaryOperator::normalize(OperandStack& operand_stack) const {
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