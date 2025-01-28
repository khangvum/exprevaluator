# exprevaluator

A Windows console application that ***evaluates mathematical expressions*** involving ***multiple operators*** and ***functions***. It supports operations on ***a variety of data types***, including Boolean, Integer, Real, and Variable.

## Features

-   Supports ***various operators***:

Type            |   Operators
:---------------|:----------------------------------------------------------------
**Unary**       |   Negation (`-x`), Not (`!x`), Factorial (`x!`)
**Arithmetic**  |   Addition (`+`), Subtraction (`-`), Multiplication (`*`), Division (`/`), Modulus (`%`), Power (`**`)
**Assignment**  |   Assignment (`=`)
**Logical**     |   And (`&&`), Nand (`!&&`), Or (`\|\|`), Nor (`!\|\|`)
**Relational**  |   Equality (`==`), Inequality (`!=`), Greater (`>`), GreaterEqual (`>=`), Less (`<`), LessEqual (`<=`)
**Bitwise**     |   Xor (`^`), Xnor (`!^`)

-   Includes ***built-in functions***:

Type            |   Functions
:---------------|:----------------------------------------------------------------
**One-Argument**|   `abs`, `arccos`, `arcsin`, `arctan`, `ceil`, `cos`, `exp`, `floor`, `lb`, `ln`, `log`, `sin`, `sqrt`, `tan`
**Two-Argument**|   `arctan2`, `max`, `min`, `pow`

-   Handles ***multiple data types***: Boolean, Integer, Real, and Variable.
-   Supports ***nested expressions*** and ***parentheses*** for complex calculations.
-   Simple, fast, and lightweight ***console-based*** interface.

## Shunting Yard Algorithm

The shunting yard algorithm is a method for parsing ***infix notation*** to ***postfix notation***, also known as ***reverse Polish notation*** (***RPN***).

-   A mathematical notation in which ***operators follow their operands***.
-   The notation does not need any ***parentheses*** for as long as each operator has a ***fixed number of operands***.
-   Algorithm:

```powershell
Set postfix queue to empty.
Set operation stack to empty.
For each token in the infix queue.
	If the token is an operand then,
		Append the token to the postfix queue.
	Else if the token is a function then,
		Push the token on to the operation stack.
	Else if the token is an argument separator then,
		While the top meta-operation on the operation stack is not a left parenthesis do,
			Pop the operation from the operation stack.
			Append that operation to the postfix queue.
	Else if the token is an left parenthesis then,
		Push the token on to the operation stack.
	Else if the token is a right parenthesis then,
		While the top meta-operation on the operation stack is not a left parenthesis do,
			Pop the operation from the operation stack.
			Append that operation to the postfix queue.
		If the operation stack is empty then,
			Exception “Right parenthesis, has no matching left parenthesis”
		Pop the left parenthesis from the operation stack.
		If the top of the operation stack is a function then,
			Pop the function from the operation stack
			Append that function to the postfix queue.
	Else if the token is an operator then,
		While the operation stack is not empty do
			If the top of the operation stack is not an operator then,
				Exit the while loop.
			If the token is a non-associative operator then,
				Exit the while loop.
			If the token is a left-associative operator and 
			has greater precedence than the top of the operation stack then,
				Exit the while loop.
			If the token is a right-associative operator and 
				has greater or equal precedence than the top of the operation stack then,
				Exit the while loop.
			Pop an operator from the top of the operation stack.
			Append that operator to the postfix queue.
		End while
		Push the token on to the operation stack.
	Else
		Exception “Unknown token”.
End for-each
While the operation stack is not empty do
	If the top of the operation stack is a left-parenthesis then,
		Exception “Missing right-parenthesis”.
	Pop an operator from the top of the operation stack.
	Append that operator to the postfix queue.
Return postfix queue
Set postfix queue to empty.
Set operation stack to empty.
For each token in the infix queue.
	If the token is an operand then,
		Append the token to the postfix queue.
	Else if the token is a function then,
		Push the token on to the operation stack.
	Else if the token is an argument separator then,
		While the top meta-operation on the operation stack is not a left parenthesis do,
			Pop the operation from the operation stack.
			Append that operation to the postfix queue.
	Else if the token is an left parenthesis then,
		Push the token on to the operation stack.
	Else if the token is a right parenthesis then,
		While the top meta-operation on the operation stack is not a left parenthesis do,
			Pop the operation from the operation stack.
			Append that operation to the postfix queue.
		If the operation stack is empty then,
			Exception “Right parenthesis, has no matching left parenthesis”
		Pop the left parenthesis from the operation stack.
		If the top of the operation stack is a function then,
			Pop the function from the operation stack
			Append that function to the postfix queue.
	Else if the token is an operator then,
		While the operation stack is not empty do
			If the top of the operation stack is not an operator then,
				Exit the while loop.
			If the token is a non-associative operator then,
				Exit the while loop.
			If the token is a left-associative operator and 
			has greater precedence than the top of the operation stack then,
				Exit the while loop.
			If the token is a right-associative operator and 
				has greater or equal precedence than the top of the operation stack then,
				Exit the while loop.
			Pop an operator from the top of the operation stack.
			Append that operator to the postfix queue.
		End while
		Push the token on to the operation stack.
	Else
		Exception “Unknown token”.
End for-each
While the operation stack is not empty do
	If the top of the operation stack is a left-parenthesis then,
		Exception “Missing right-parenthesis”.
	Pop an operator from the top of the operation stack.
	Append that operator to the postfix queue.
Return postfix queue
```

-   Example:

Infix notation  |   Postfix Notation (Reverse Polish Notation)
:--------------:|:---------------------------------------------------------------:
3 + 4           |   3 4 +
3 x 6 + 4       |   3 6 x 4 +
(5 - 6) x 7     |   5 6 - 7 x
11 x 7 + 6 ÷ 3  |   11 7 x 6 3 ÷ +
5 ** 2 ** 3     |   5 2 3 ** **

## Architecture

![Sequence Diagram](!docs/Sequence%20Diagram.jpg)