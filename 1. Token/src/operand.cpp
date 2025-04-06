/*! \file	    operand.cpp
	\brief	    Operand class definition and utilities
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Definition of the Operand classes derived from Token class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "../inc/operand.hpp"
#include <stdexcept>
using namespace std;

<<<<<<< HEAD
namespace exprevaluator {
	// 1. Unary operators
	DEFINE_OPERATION(Operand, perform_negation) {
		throw runtime_error("Error: Cannot perform: <Negation>");
	}
	DEFINE_OPERATION(Operand, perform_not) {
		throw runtime_error("Error: Cannot perform: <Not>");
	}
	DEFINE_OPERATION(Operand, perform_factorial) {
		throw runtime_error("Error: Cannot perform: <Factorial>");
	}

	// 2. Binary operators
	// - Arithmetic
	DEFINE_OPERATION(Operand, perform_addition) {
		throw runtime_error("Error: Cannot perform: <Addition>");
	}
	DEFINE_OPERATION(Operand, perform_subtraction) {
		throw runtime_error("Error: Cannot perform: <Subtraction>");
	}
	DEFINE_OPERATION(Operand, perform_multiplication) {
		throw runtime_error("Error: Cannot perform: <Multiplication>");
	}
	DEFINE_OPERATION(Operand, perform_division) {
		throw runtime_error("Error: Cannot perform: <Division>");
	}
	DEFINE_OPERATION(Operand, perform_modulus) {
		throw runtime_error("Error: Cannot perform: <Modulus>");
	}
	DEFINE_OPERATION(Operand, perform_power) {
		throw runtime_error("Error: Cannot perform: <Power>");
	}

	// - Assignment
	DEFINE_OPERATION(Operand, perform_assignment) {
		throw runtime_error("Error: Cannot perform: <Assignment>");
	}

	// - Logical
	DEFINE_OPERATION(Operand, perform_and) {
		throw runtime_error("Error: Cannot perform: <And>");
	}
	DEFINE_OPERATION(Operand, perform_nand) {
		throw runtime_error("Error: Cannot perform: <Nand>");
	}
	DEFINE_OPERATION(Operand, perform_nor) {
		throw runtime_error("Error: Cannot perform: <Nor>");
	}
	DEFINE_OPERATION(Operand, perform_or) {
		throw runtime_error("Error: Cannot perform: <Or>");
	}

	// - Relational
	DEFINE_OPERATION(Operand, perform_equality) {
		throw runtime_error("Error: Cannot perform: <Equality>");
	}
	DEFINE_OPERATION(Operand, perform_greater) {
		throw runtime_error("Error: Cannot perform: <Greater>");
	}
	DEFINE_OPERATION(Operand, perform_greater_equal) {
		throw runtime_error("Error: Cannot perform: <GreaterEqual>");
	}
	DEFINE_OPERATION(Operand, perform_inequality) {
		throw runtime_error("Error: Cannot perform: <Inequality>");
	}
	DEFINE_OPERATION(Operand, perform_less) {
		throw runtime_error("Error: Cannot perform: <Less>");
	}
	DEFINE_OPERATION(Operand, perform_less_equal) {
		throw runtime_error("Error: Cannot perform: <LessEqual>");
	}

	// - Bitwise
	DEFINE_OPERATION(Operand, perform_xor) {
		throw runtime_error("Error: Cannot perform: <Xor>");
	}
	DEFINE_OPERATION(Operand, perform_xnor) {
		throw runtime_error("Error: Cannot perform: <Xnor>");
	}

	// 3. One-Argument Functions
	DEFINE_OPERATION(Operand, perform_abs) {
		throw runtime_error("Error: Cannot perform: <Abs>");
	}
	DEFINE_OPERATION(Operand, perform_arccos) {
		throw runtime_error("Error: Cannot perform: <Arccos>");
	}
	DEFINE_OPERATION(Operand, perform_arcsin) {
		throw runtime_error("Error: Cannot perform: <Arcsin>");
	}
	DEFINE_OPERATION(Operand, perform_arctan) {
		throw runtime_error("Error: Cannot perform: <Arctan>");
	}
	DEFINE_OPERATION(Operand, perform_ceil) {
		throw runtime_error("Error: Cannot perform: <Ceil>");
	}
	DEFINE_OPERATION(Operand, perform_cos) {
		throw runtime_error("Error: Cannot perform: <Cos>");
	}
	DEFINE_OPERATION(Operand, perform_exp) {
		throw runtime_error("Error: Cannot perform: <Exp>");
	}
	DEFINE_OPERATION(Operand, perform_floor) {
		throw runtime_error("Error: Cannot perform: <Floor>");
	}
	DEFINE_OPERATION(Operand, perform_lb) {
		throw runtime_error("Error: Cannot perform: <Lb>");
	}
	DEFINE_OPERATION(Operand, perform_ln) {
		throw runtime_error("Error: Cannot perform: <Ln>");
	}
	DEFINE_OPERATION(Operand, perform_log) {
		throw runtime_error("Error: Cannot perform: <Log>");
	}
	DEFINE_OPERATION(Operand, perform_sin) {
		throw runtime_error("Error: Cannot perform: <Sin>");
	}
	DEFINE_OPERATION(Operand, perform_sqrt) {
		throw runtime_error("Error: Cannot perform: <Sqrt>");
	}
	DEFINE_OPERATION(Operand, perform_tan) {
		throw runtime_error("Error: Cannot perform: <Tan>");
	}

	// 4. Two-Argument Functions
	DEFINE_OPERATION(Operand, perform_arctan2) {
		throw runtime_error("Error: Cannot perform: <Arctan2>");
	}
	DEFINE_OPERATION(Operand, perform_max) {
		throw runtime_error("Error: Cannot perform: <Max>");
	}
	DEFINE_OPERATION(Operand, perform_min) {
		throw runtime_error("Error: Cannot perform: <Min>");
	}
	DEFINE_OPERATION(Operand, perform_pow) {
		throw runtime_error("Error: Cannot perform: <Pow>");
	}
}	// End of namespace exprevaluator
=======
// 1. Unary operators
DEFINE_OPERATION(Operand, perform_negation) {
	throw runtime_error("Error: Cannot perform: <Negation>");
}
DEFINE_OPERATION(Operand, perform_not) {
	throw runtime_error("Error: Cannot perform: <Not>");
}
DEFINE_OPERATION(Operand, perform_factorial) {
	throw runtime_error("Error: Cannot perform: <Factorial>");
}

// 2. Binary operators
// - Arithmetic
DEFINE_OPERATION(Operand, perform_addition) {
	throw runtime_error("Error: Cannot perform: <Addition>");
}
DEFINE_OPERATION(Operand, perform_subtraction) {
	throw runtime_error("Error: Cannot perform: <Subtraction>");
}
DEFINE_OPERATION(Operand, perform_multiplication) {
	throw runtime_error("Error: Cannot perform: <Multiplication>");
}
DEFINE_OPERATION(Operand, perform_division) {
	throw runtime_error("Error: Cannot perform: <Division>");
}
DEFINE_OPERATION(Operand, perform_modulus) {
	throw runtime_error("Error: Cannot perform: <Modulus>");
}
DEFINE_OPERATION(Operand, perform_power) {
	throw runtime_error("Error: Cannot perform: <Power>");
}

// - Assignment
DEFINE_OPERATION(Operand, perform_assignment) {
	throw runtime_error("Error: Cannot perform: <Assignment>");
}

// - Logical
DEFINE_OPERATION(Operand, perform_and) {
	throw runtime_error("Error: Cannot perform: <And>");
}
DEFINE_OPERATION(Operand, perform_nand) {
	throw runtime_error("Error: Cannot perform: <Nand>");
}
DEFINE_OPERATION(Operand, perform_nor) {
	throw runtime_error("Error: Cannot perform: <Nor>");
}
DEFINE_OPERATION(Operand, perform_or) {
	throw runtime_error("Error: Cannot perform: <Or>");
}

// - Relational
DEFINE_OPERATION(Operand, perform_equality) {
	throw runtime_error("Error: Cannot perform: <Equality>");
}
DEFINE_OPERATION(Operand, perform_greater) {
	throw runtime_error("Error: Cannot perform: <Greater>");
}
DEFINE_OPERATION(Operand, perform_greater_equal) {
	throw runtime_error("Error: Cannot perform: <GreaterEqual>");
}
DEFINE_OPERATION(Operand, perform_inequality) {
	throw runtime_error("Error: Cannot perform: <Inequality>");
}
DEFINE_OPERATION(Operand, perform_less) {
	throw runtime_error("Error: Cannot perform: <Less>");
}
DEFINE_OPERATION(Operand, perform_less_equal) {
	throw runtime_error("Error: Cannot perform: <LessEqual>");
}

// - Bitwise
DEFINE_OPERATION(Operand, perform_xor) {
	throw runtime_error("Error: Cannot perform: <Xor>");
}
DEFINE_OPERATION(Operand, perform_xnor) {
	throw runtime_error("Error: Cannot perform: <Xnor>");
}

// 3. One-Argument Functions
DEFINE_OPERATION(Operand, perform_abs) {
	throw runtime_error("Error: Cannot perform: <Abs>");
}
DEFINE_OPERATION(Operand, perform_arccos) {
	throw runtime_error("Error: Cannot perform: <Arccos>");
}
DEFINE_OPERATION(Operand, perform_arcsin) {
	throw runtime_error("Error: Cannot perform: <Arcsin>");
}
DEFINE_OPERATION(Operand, perform_arctan) {
	throw runtime_error("Error: Cannot perform: <Arctan>");
}
DEFINE_OPERATION(Operand, perform_ceil) {
	throw runtime_error("Error: Cannot perform: <Ceil>");
}
DEFINE_OPERATION(Operand, perform_cos) {
	throw runtime_error("Error: Cannot perform: <Cos>");
}
DEFINE_OPERATION(Operand, perform_exp) {
	throw runtime_error("Error: Cannot perform: <Exp>");
}
DEFINE_OPERATION(Operand, perform_floor) {
	throw runtime_error("Error: Cannot perform: <Floor>");
}
DEFINE_OPERATION(Operand, perform_lb) {
	throw runtime_error("Error: Cannot perform: <Lb>");
}
DEFINE_OPERATION(Operand, perform_ln) {
	throw runtime_error("Error: Cannot perform: <Ln>");
}
DEFINE_OPERATION(Operand, perform_log) {
	throw runtime_error("Error: Cannot perform: <Log>");
}
DEFINE_OPERATION(Operand, perform_sin) {
	throw runtime_error("Error: Cannot perform: <Sin>");
}
DEFINE_OPERATION(Operand, perform_sqrt) {
	throw runtime_error("Error: Cannot perform: <Sqrt>");
}
DEFINE_OPERATION(Operand, perform_tan) {
	throw runtime_error("Error: Cannot perform: <Tan>");
}

// 4. Two-Argument Functions
DEFINE_OPERATION(Operand, perform_arctan2) {
	throw runtime_error("Error: Cannot perform: <Arctan2>");
}
DEFINE_OPERATION(Operand, perform_max) {
	throw runtime_error("Error: Cannot perform: <Max>");
}
DEFINE_OPERATION(Operand, perform_min) {
	throw runtime_error("Error: Cannot perform: <Min>");
}
DEFINE_OPERATION(Operand, perform_pow) {
	throw runtime_error("Error: Cannot perform: <Pow>");
}
>>>>>>> origin/master
