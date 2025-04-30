/*! \file	    RPNEvaluator.cpp
	\brief	    RPNEvaluator class definition
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

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

#include "../inc/RPNEvaluator.hpp"
#include "../../1. Token/inc/function.hpp"
#include <stdexcept>
using namespace std;

namespace exprevaluator {
	[[nodiscard]] Operand::pointer_type RPNEvaluator::evaluate(const TokenList& postfix_tokens) {
		OperandStack operand_stack;

		for (const auto& token : postfix_tokens) {
			if (is<Operand>(token))
				operand_stack.push(convert<Operand>(token));
			else {
				Operation::pointer_type operation{ convert<Operation>(token) };
				if (operation->number_of_args() > operand_stack.size())
					throw runtime_error("Error: insufficient parameters to " + operation->str());

				if (is<Result>(operation)) {
					Result::pointer_type result_ptr{ convert<Result>(operation) };
					result_ptr->set_results(results_);
				}

				Operand::pointer_type result{ operation->perform(operand_stack) };
				operand_stack.push(result);
			}
		}

		if (operand_stack.size() > 1)
			throw runtime_error("Error: too many operands");
		if (operand_stack.empty())
			throw runtime_error("Error: insufficient operands");

		results_[results_.size() + 1] = operand_stack.top();
		return operand_stack.top();
	}
}	// End of namespace exprevaluator