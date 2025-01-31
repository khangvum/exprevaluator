```mermaid
---
title: Token
---
classDiagram
    class Token

    class Operand {
        +perform_addition(valueStack)
    }

    class Operation {
        +perform(valueStack)
    }

    class PseudoOperation

    class Operator {
        +precedence(): Precedence Category
    }

    class Function

    class Parenthesis

    class ArgumentSeparator

    class LeftParenthesis

    class RightParenthesis

    Token <|-- Operand
    Token <|-- Operation
    Token <|-- PseudoOperation
    PseudoOperation <|-- Parenthesis
    PseudoOperation <|-- ArgumentSeparator
    Parenthesis <|-- LeftParenthesis
    Parenthesis <|-- RightParenthesis
    Operation <|-- Operator
    Operation <|-- Function
```