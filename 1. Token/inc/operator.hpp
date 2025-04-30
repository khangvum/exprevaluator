#pragma once
/*! \file	    operator.hpp
	\brief	    Operator class declaration
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declarations of the Operator classes derived from Operation
  class, including the subclasses:

		enum class Precendence
		DEF_PRECEDENCE()
		class Operator
			class BinaryOperator
				class RAssocOperator
					class Power
					class Assignment
				class LAssocOperator
					class Addition
					class And
					class Division
					class Equality
					class Greater
					class GreaterEqual
					class Inequality
					class Less
					class LessEqual
					class Multiplication
					class Modulus
					class Nand
					class Nor
					class Or
					class Subtraction
					class Xor
					class Xnor
			class NonAssociative
				class UnaryOperator
					class Identity
					class Negation
					class Not
					class PostfixOperator
						class Factorial

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

#include "operation.hpp"
#include "variable.hpp"
#include <stdexcept>

namespace exprevaluator {
	// Operator Precedence values
	enum class Precedence { MIN = 0,
		ASSIGNMENT, LOGOR, LOGXOR, LOGAND, BITOR,
		BITXOR, BITAND, EQUALITY, RELATIONAL, BITSHIFT,
		ADDITIVE, MULTIPLICATIVE, UNARY, POWER, POSTFIX,
		MAX
	};

	// Define a precedence category method used inside a class declaration
	#define DEF_PRECEDENCE(category)\
		[[nodiscard]] Precedence precedence() const override { return Precedence::category; }

	// Operator base class
	class Operator : public Operation {
	public:
		DEF_POINTER_TYPE(Operator)
		[[nodiscard]] virtual Precedence precedence() const = 0;
	};

			// BinaryOperator base class
			class BinaryOperator : public Operator {
			public:
				[[nodiscard]]	virtual unsigned number_of_args() const override { return 2; }
								virtual void normalize(OperandStack& operand_stack) const override;
			};

					// RAssocOperator base class
					class RAssocOperator : public BinaryOperator {};

							// Power class
							class Power : public RAssocOperator {
							public:
								DEF_PRECEDENCE(POWER)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_power(operand_stack);
								}
							};

							// Assignment class
							class Assignment : public RAssocOperator {
							public:
								DEF_PRECEDENCE(ASSIGNMENT)
								DEFINE_PURE_OPERATION(perform) {
									auto rhs{ operand_stack.top() }; operand_stack.pop();
									auto lhs{ operand_stack.top() }; operand_stack.pop();
									if (!is<Variable>(lhs))
										throw std::runtime_error("Error: assignment to a non-variable.");

									auto variable{ convert<Variable>(lhs) };
									if (is<Operand>(rhs))
										variable->set(rhs);
									return convert<Operand>(variable);
								}
							};

					// LAssocOperator base class
					class LAssocOperator : public BinaryOperator {};

							// Addition class
							class Addition : public LAssocOperator {
							public:
								DEF_PRECEDENCE(ADDITIVE)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_addition(operand_stack);
								}
							};

							// And class
							class And : public LAssocOperator {
							public:
								DEF_PRECEDENCE(LOGAND)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_and(operand_stack);
								}
							};

							// Division class
							class Division : public LAssocOperator {
							public:
								DEF_PRECEDENCE(MULTIPLICATIVE)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_division(operand_stack);
								}
							};

							// Equality class
							class Equality : public LAssocOperator {
							public:
								DEF_PRECEDENCE(EQUALITY)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_equality(operand_stack);
								}
							};

							// Greater class
							class Greater : public LAssocOperator {
							public:
								DEF_PRECEDENCE(RELATIONAL)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_greater(operand_stack);
								}
							};

							// GreaterEqual class
							class GreaterEqual : public LAssocOperator {
							public:
								DEF_PRECEDENCE(RELATIONAL)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_greater_equal(operand_stack);
								}
							};

							// Inequality class
							class Inequality : public LAssocOperator {
							public:
								DEF_PRECEDENCE(EQUALITY)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_inequality(operand_stack);
								}
							};

							// Less class
							class Less : public LAssocOperator {
							public:
								DEF_PRECEDENCE(RELATIONAL)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_less(operand_stack);
								}
							};

							// LessEqual class
							class LessEqual : public LAssocOperator {
							public:
								DEF_PRECEDENCE(RELATIONAL)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_less_equal(operand_stack);
								}
							};

							// Multiplication class
							class Multiplication : public LAssocOperator {
							public:
								DEF_PRECEDENCE(MULTIPLICATIVE)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_multiplication(operand_stack);
								}
							};

							// Modulus class
							class Modulus : public LAssocOperator {
							public:
								DEF_PRECEDENCE(MULTIPLICATIVE)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_modulus(operand_stack);
								}
							};

							// Nand class
							class Nand : public LAssocOperator {
							public:
								DEF_PRECEDENCE(LOGAND)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_nand(operand_stack);
								}
							};

							// Nor class
							class Nor : public LAssocOperator {
							public:
								DEF_PRECEDENCE(LOGOR)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_nor(operand_stack);
								}
							};

							// Or class
							class Or : public LAssocOperator {
							public:
								DEF_PRECEDENCE(LOGOR)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_or(operand_stack);
								}
							};

							// Subtraction class
							class Subtraction : public LAssocOperator {
							public:
								DEF_PRECEDENCE(ADDITIVE)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_subtraction(operand_stack);
								}
							};

							// Xor class
							class Xor : public LAssocOperator {
							public:
								DEF_PRECEDENCE(LOGOR)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_xor(operand_stack);
								}
							};

							// Xnor class
							class Xnor : public LAssocOperator {
							public:
								DEF_PRECEDENCE(LOGOR)
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_xnor(operand_stack);
								}
							};

			// NonAssociative base class
			class NonAssociative : public Operator {};

					// UnaryOperator base class
					class UnaryOperator : public NonAssociative {
					public:
						DEF_PRECEDENCE(UNARY)
						[[nodiscard]]	virtual unsigned number_of_args() const override { return 1; }
										virtual void normalize(OperandStack& operand_stack) const override;
					};

							// Identity class
							class Identity : public UnaryOperator {
							public:
								DEFINE_PURE_OPERATION(perform) {
									auto operand{ operand_stack.top() }; operand_stack.pop();
									return operand;
								}
							};

							// Negation class
							class Negation : public UnaryOperator {
							public:
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_negation(operand_stack);
								}
							};

							// Not class
							class Not : public UnaryOperator {
							public:
								DEFINE_PURE_OPERATION(perform) {
									normalize(operand_stack);
									return operand_stack.top()->perform_not(operand_stack);
								}
							};

							// Postfix class
							class PostfixOperator : public UnaryOperator {};

									// Factorial class
									class Factorial : public PostfixOperator {
									public:
										DEFINE_PURE_OPERATION(perform) {
											normalize(operand_stack);
											return operand_stack.top()->perform_factorial(operand_stack);
										}
									};
}	// End of namespace exprevaluator