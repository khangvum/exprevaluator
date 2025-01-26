# exprevaluator

A Windows console application that evaluates mathematical expressions involving multiple operators and functions. It supports operations on a variety of data types, including Boolean, Integer, Real, and Variable.

## Features

-   Supports various operators:

Type        |   Operators
:-----------|:----------------------------------------------------------------
Unary       |   Negation (`-x`), Not (`!x`), Factorial (`x!`)
Arithmetic  |   Addition (`+`), Subtraction (`-`), Multiplication (`*`), Division (`/`), Modulus (`%`), Power (`**`)
Assignment  |   Assignment (`=`)
Logical     |   And (`&&`), Nand (`!&&`), Or (`||`), Nor (`!||`)
Relational  |   Equality (`==`), Inequality (`!=`), Greater (`>`), GreaterEqual (`>=`), Less (`<`), LessEqual (`<=`)
Bitwise     |   Xor (`^`), Xnor (`!^`)

-   Includes built-in functions

Type        |   Functions</th>
:-----------|:----------------------------------------------------------------
One-Argument|   `abs`, `arccos`, `arcsin`, `arctan`, `ceil`, `cos`, `exp`, `floor`, `lb`, `ln`, `log`, `sin`, `sqrt`, `tan`
Two-Argument|   `arctan2`, `max`, `min`, `pow`

-   Handles multiple data types: Boolean, Integer, Real, and Variable.
-   Supports nested expressions and parentheses for complex calculations.
-   Simple, fast, and lightweight console-based interface.

## Architecture

![Sequence Diagram](!docs/Sequence%20Diagram.jpg)