/*! \file	    expression_evaluator.cpp
	\brief	    ExpressionEvaluator class definition
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "../inc/expression_evaluator.hpp"
using namespace std;

<<<<<<< HEAD
namespace exprevaluator {
	[[nodiscard]] ExpressionEvaluator::result_type ExpressionEvaluator::evaluate(const expression_type& expression) {
		// Tokenize the expression
		TokenList infix_tokens{ tokenizer_.tokenize(expression) };

		// Parse the infix tokens into postfix tokens
		TokenList postfix_tokens{ parser_.parse(infix_tokens) };

		// Evaluate the postfix tokens
		Operand::pointer_type result{ rpn_evaluator_.evaluate(postfix_tokens) };

		return result;
	}
}	// End of namespace exprevaluator
=======
[[nodiscard]] ExpressionEvaluator::result_type ExpressionEvaluator::evaluate(const expression_type& expression) {
	// Tokenize the expression
	TokenList infix_tokens{ tokenizer_.tokenize(expression) };

	// Parse the infix tokens into postfix tokens
	TokenList postfix_tokens{ parser_.parse(infix_tokens) };

	// Evaluate the postfix tokens
	Operand::pointer_type result{ rpn_evaluator_.evaluate(postfix_tokens) };

	return result;
}
>>>>>>> origin/master
