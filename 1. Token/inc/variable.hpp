#pragma once
/*! \file	    variable.hpp
	\brief	    Variable class declaration
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declaration of the Variable classes derived from Operand 
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


#include "operand.hpp"

namespace exprevaluator {
	// Variable class
	class Variable : public Operand {
	public:
		using value_type = Operand::pointer_type;
		DEF_POINTER_TYPE(Variable)
	private:
		value_type	value_;
	public:
		constexpr Variable() = default;
		[[nodiscard]] value_type	value() const { return value_; }
							void	set(const value_type& value) { value_ = value; }
		[[nodiscard]] string_type	str() const override;
	};
}	// End of namespace exprevaluator