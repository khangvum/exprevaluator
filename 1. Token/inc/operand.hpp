#pragma once
/*! \file	    operand.hpp
	\brief	    Operand class declaration and utilities
    \author	    Khang Vu
    \date	    2025-01-06
    \copyright	Khang Vu

  =============================================================
  Declaration of the Operand classes derived from Token class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
      Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "token.hpp"
#include <cassert>
#include <deque>
#include <stack>

namespace exprevaluator {
    // Operand base class
    class Operand : public Token {
    public:
        DEF_POINTER_TYPE(Operand)
            using operand_list_type = std::deque<Operand::pointer_type>;
        using operand_stack_type = std::stack<Operand::pointer_type>;

        // Operations
        /*	\brief		Perform an operation on the operand stack
            \param		operand_stack_type&     - The operand stack
            \return		Operand::pointer_type   - The pointer to the result
        */
#define DECLARE_OPERATION(name)\
        [[nodiscard]] virtual Operand::pointer_type name(operand_stack_type& operand_stack) const;
        // 1. Unary operators
        DECLARE_OPERATION(perform_negation)
        DECLARE_OPERATION(perform_not)
        DECLARE_OPERATION(perform_factorial)

        // 2. Binary operators
        // - Arithmetic
        DECLARE_OPERATION(perform_addition)
        DECLARE_OPERATION(perform_subtraction)
        DECLARE_OPERATION(perform_multiplication)
        DECLARE_OPERATION(perform_division)
        DECLARE_OPERATION(perform_modulus)
        DECLARE_OPERATION(perform_power)

        // - Assignment
        DECLARE_OPERATION(perform_assignment)

        // - Logical
        DECLARE_OPERATION(perform_and)
        DECLARE_OPERATION(perform_nand)
        DECLARE_OPERATION(perform_nor)
        DECLARE_OPERATION(perform_or)

        // - Relational
        DECLARE_OPERATION(perform_equality)
        DECLARE_OPERATION(perform_greater)
        DECLARE_OPERATION(perform_greater_equal)
        DECLARE_OPERATION(perform_inequality)
        DECLARE_OPERATION(perform_less)
        DECLARE_OPERATION(perform_less_equal)

        // - Bitwise
        DECLARE_OPERATION(perform_xor)
        DECLARE_OPERATION(perform_xnor)

        // 3. One-Argument Functions
        DECLARE_OPERATION(perform_abs)
        DECLARE_OPERATION(perform_arccos)
        DECLARE_OPERATION(perform_arcsin)
        DECLARE_OPERATION(perform_arctan)
        DECLARE_OPERATION(perform_ceil)
        DECLARE_OPERATION(perform_cos)
        DECLARE_OPERATION(perform_exp)
        DECLARE_OPERATION(perform_floor)
        DECLARE_OPERATION(perform_lb)
        DECLARE_OPERATION(perform_ln)
        DECLARE_OPERATION(perform_log)
        DECLARE_OPERATION(perform_sin)
        DECLARE_OPERATION(perform_sqrt)
        DECLARE_OPERATION(perform_tan)

        // 4. Two-Argument Functions
        DECLARE_OPERATION(perform_arctan2)
        DECLARE_OPERATION(perform_max)
        DECLARE_OPERATION(perform_min)
        DECLARE_OPERATION(perform_pow)
#undef DECLARE_OPERATION
    };

    // Make a new smart-pointer managed Token object with constructor parameter
    template<typename T, class... Args> [[nodiscard]] inline
        Operand::pointer_type make_operand(Args... params) {
        return Operand::pointer_type(new T(params...));
    }

    // Get the value from an operand
    template <typename OPERAND_TYPE> [[nodiscard]]
        typename OPERAND_TYPE::value_type value_of(Token::pointer_type operand) {
            assert(is<OPERAND_TYPE>(operand));
            return dynamic_cast<OPERAND_TYPE*>(operand.get())->value();
        }

        // Type for a list & stack of operands
        using OperandList = Operand::operand_list_type;
        using OperandStack = Operand::operand_stack_type;

        // Macros for defining operations & overriding operations in subclasses
#define DEFINE_OPERATION(class_name, name)\
        [[nodiscard]] Operand::pointer_type class_name::name(OperandStack& operand_stack) const
#define OVERRIDE_OPERATION(name)\
        [[nodiscard]] virtual Operand::pointer_type name(OperandStack& operand_stack) const override;
}   // End of namespace exprevaluator