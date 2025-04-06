#pragma once
/*! \file	    RPNEvaluator.hpp
	\brief	    RPNEvaluator class declaration
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

#include "../../1. Token/inc/operand.hpp"
#include "../../1. Token/inc/operation.hpp"

namespace exprevaluator {
	class RPNEvaluator {
		// Block copy operator & constructor
		RPNEvaluator(const RPNEvaluator&) = delete;
		RPNEvaluator& operator = (const RPNEvaluator&) = delete;

		// Attribute
		Operation::map_type results_;
	public:
		RPNEvaluator() = default;
		[[nodiscard]] Operand::pointer_type evaluate(const TokenList& postfix_tokens);
	};
}	// End of namespace exprevaluator