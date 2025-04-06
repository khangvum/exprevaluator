#pragma once
/*! \file	    function.hpp
	\brief	    Function class declaration
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declarations of the Function classes derived from Operation
  class, including the subclasses:

		class OneArgFunction
			class Abs
			class Arccos
			class Arcsin
			class Arctan
			class Ceil
			class Cos
			class Exp
			class Floor
			class Lb
			class Ln
			class Log
			class Result
			class Sin
			class Sqrt
			class Tan
		class TwoArgFunction
			class Arctan2
			class Max
			class Min
			class Pow
		class ThreeArgFunction

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "operation.hpp"
#include "integer.hpp"
#include "gregorian.hpp"
#include <stdexcept>

namespace exprevaluator {
	// Function base class
	class Function : public Operation {};

			// OneArgFunction base class
			class OneArgFunction : public Function {
			public:
				[[nodiscard]]	virtual unsigned number_of_args() const override { return 1; }
								virtual void normalize(OperandStack& operand_stack) const override;
			};

					// Abs (Absolute) class
					class Abs : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_abs(operand_stack);
						}
					};

					// Arccos (Arc cosine) class
					class Arccos : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_arccos(operand_stack);
						}
					};

					// Arcsin (Arc sine) class
					class Arcsin : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_arcsin(operand_stack);
						}
					};

					// Arctan (Arc tangent) class
					class Arctan : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_arctan(operand_stack);
						}
					};

					// Ceil class
					class Ceil : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_ceil(operand_stack);
						}
					};

					// Cos (Cosine) class
					class Cos : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_cos(operand_stack);
						}
					};

					// Exp (Exponential) class
					class Exp : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_exp(operand_stack);
						}
					};

					// Floor class
					class Floor : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_floor(operand_stack);
						}
					};

					// Lb (Logarithm base 2) class
					class Lb : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_lb(operand_stack);
						}
					};

					// Ln (Natural logarithm) class
					class Ln : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_ln(operand_stack);
						}
					};

					// Log (logarithm base 10) class
					class Log : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_log(operand_stack);
						}
					};

					// Result class
					class Result : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							auto index_ptr{ operand_stack.top() }; operand_stack.pop();

							if (!is<Integer>(index_ptr))
								throw std::runtime_error("Cannot convert");

							auto index{ value_of<Integer>(index_ptr) };
							if (index < 1)
								throw std::runtime_error("Result index is below range.");
							else if (index > results_.size())
								throw std::runtime_error("Result index is above range.");

							return results_.at(index);
						}
					};

					// Sin (Sine) class
					class Sin : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_sin(operand_stack);
						}
					};

					// Sqrt (Square root) class
					class Sqrt : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_sqrt(operand_stack);
						}
					};

					// Tan (Tangent) class
					class Tan : public OneArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_tan(operand_stack);
						}
					};

			// TwoArgFunction base class
			class TwoArgFunction : public Function {
			public:
				[[nodiscard]]	virtual unsigned number_of_args() const override { return 2; }
								virtual void normalize(OperandStack& operand_stack) const override;
			};

					// Artan2 (2-parameter arc tangent) class
					// - First argument: The change in Y
					// - Second argument: The change in X
					class Arctan2 : public TwoArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_arctan2(operand_stack);
						}
					};

					// Max (Maximum) class
					class Max : public TwoArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_max(operand_stack);
						}
					};

					// Min (Minimum) class
					class Min : public TwoArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_min(operand_stack);
						}
					};

					// Pow class
					class Pow : public TwoArgFunction {
					public:
						DEFINE_PURE_OPERATION(perform) {
							normalize(operand_stack);
							return operand_stack.top()->perform_pow(operand_stack);
						}
					};

			// ThreeArgFunction base class
			class ThreeArgFunction : public Function {
			public:
				[[nodiscard]]	virtual unsigned number_of_args() const override { return 3; }
			};

				// GregorianFunc class
				class GregorianFunc : public ThreeArgFunction {
				public:
					DEFINE_PURE_OPERATION(perform) {
						auto day{ value_of<Integer>(operand_stack.top()) }; operand_stack.pop();
						auto month{ value_of<Integer>(operand_stack.top()) }; operand_stack.pop();
						auto year{ value_of<Integer>(operand_stack.top()) }; operand_stack.pop();

						return convert<Operand>(make<Gregorian>());
					}
				};
}	// End of namespace exprevaluator