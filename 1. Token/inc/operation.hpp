#pragma once
/*! \file	    operation.hpp
	\brief	    Operation class declaration
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declaration of the Operation classes derived from Token
  class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "token.hpp"
#include "operand.hpp"
#include "integer.hpp"
#include <map>

namespace exprevaluator {
	// Operation class
	class Operation : public Token {
	public:
		using map_type = std::map<Integer::value_type, Operand::pointer_type>;
		DEF_POINTER_TYPE(Operation)
	protected:
		map_type	results_;
	public:
		/*	\brief		Get the number of arguments required by the operation
			\return		unsigned - The number of arguments
		*/
		[[nodiscard]] virtual unsigned number_of_args() const = 0;

		/*	\brief		Perform the operation
			\param		OperandStack&			- The operand stack
			\return		Operand::pointer_type   - The pointer to the result
		*/
		[[nodiscard]] virtual Operand::pointer_type perform(OperandStack& operand_stack) const = 0;

		/*	\brief		Normalize the operands (Boolean, Integer, Real, and Variable)
			\param		OperandStack&			- The operand stack
		*/
		virtual void normalize(OperandStack& operand_stack) const = 0;

		/*	\brief		Set the results of the program
			\param		map_type - The result map
		*/
		void set_results(map_type& results) { results_ = results; }
	};

		// Macro for defining pure virtual operations in subclasses
#define DEFINE_PURE_OPERATION(name)\
		[[nodiscard]] Operand::pointer_type name(OperandStack& operand_stack) const override
}	// End of namespace exprevaluator