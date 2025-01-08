#pragma once
/*! \file	    expression_evaluator.hpp
	\brief	    ExpressionEvaluator class declaration
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

#include "../../2. Tokenizer/inc/tokenizer.hpp"
#include "../../3. Parser/inc/parser.hpp"
#include "../../4. RPNEvaluator/inc/RPNEvaluator.hpp"

class ExpressionEvaluator {
public:
	using expression_type = Token::string_type;
	using result_type = Token::pointer_type;
private:
	Tokenizer		tokenizer_;
	Parser			parser_;
	RPNEvaluator	rpn_evaluator_;
public:
	[[nodiscard]] result_type evaluate(const expression_type& expression);
};