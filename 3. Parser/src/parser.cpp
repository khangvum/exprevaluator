/*! \file	    parser.cpp
    \brief	    Parser class definition
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

#include "../inc/parser.hpp"
#include "../../1. Token/inc/operand.hpp"
#include "../../1. Token/inc/function.hpp"
#include "../../1. Token/inc/operator.hpp"
#include "../../1. Token/inc/pseudo_operation.hpp"
#include <stack>
#include <stdexcept>
using namespace std;

namespace exprevaluator {
    [[nodiscard]] TokenList Parser::parse(const TokenList& infix_tokens) {
        TokenList postfix_tokens;
        stack<Token::pointer_type> operation_stack;

        for (const auto& token : infix_tokens) {
            if (is<Operand>(token))
                postfix_tokens.push_back(token);
            else if (is<Function>(token))
                operation_stack.push(token);
            else if (is<ArgumentSeparator>(token)) {
                while (!operation_stack.empty() && !is<LeftParenthesis>(operation_stack.top())) {
                    postfix_tokens.push_back(operation_stack.top());
                    operation_stack.pop();
                }
            }
            else if (is<LeftParenthesis>(token))
                operation_stack.push(token);
            else if (is<RightParenthesis>(token)) {
                while (!operation_stack.empty() && !is<LeftParenthesis>(operation_stack.top())) {
                    postfix_tokens.push_back(operation_stack.top());
                    operation_stack.pop();
                }
                if (operation_stack.empty())
                    throw runtime_error("Error: Right parenthesis has no matching left parenthesis");
                operation_stack.pop();
                if (!operation_stack.empty() && is<Function>(operation_stack.top())) {
                    postfix_tokens.push_back(operation_stack.top());
                    operation_stack.pop();
                }
            }
            else if (is<Operator>(token)) {
                while (!operation_stack.empty()) {
                    auto op1{ convert<Operator>(token) };
                    auto op2{ convert<Operator>(operation_stack.top()) };
                    if (!is<Operator>(operation_stack.top()) ||
                        is<NonAssociative>(token) ||
                        (is<LAssocOperator>(token) && op1->precedence() > op2->precedence()) ||
                        (is<RAssocOperator>(token) && op1->precedence() >= op2->precedence()))
                        break;

                    postfix_tokens.push_back(operation_stack.top());
                    operation_stack.pop();
                }
                operation_stack.push(token);
            }
            else
                throw runtime_error("Error: Unknown token");
        }

        while (!operation_stack.empty()) {
            if (is<LeftParenthesis>(operation_stack.top()))
                throw runtime_error("Error: Missing right parenthesis");
            postfix_tokens.push_back(operation_stack.top());
            operation_stack.pop();
        }

        return postfix_tokens;

    }
}   // End of namespace exprevaluator