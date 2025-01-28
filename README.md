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

<pre>
<b>Set</b> <span style="color:#38761d;"><b>postfix queue</b></span> to empty.
<b>Set</b> <span style="color:#38761d;"><b>operation stack</b></span> to empty.
<b>For each</b> token in the infix queue.
    <b>If</b> the token is an operand <b>then</b>,
		Append the token to the postfix queue.
	<b>Else if</b> the token is a function <b>then</b>,
		Push the token on to the operation stack.
	<b>Else if</b> the token is an argument separator <b>then</b>,
		<b>While</b> the top meta-operation on the operation stack is not a left parenthesis <b>do</b>,
			Pop the operation from the operation stack.
			Append that operation to the postfix queue.
	<b>Else if</b> the token is an left parenthesis <b>then</b>,
		Push the token on to the operation stack.
	<b>Else if</b> the token is a right parenthesis <b>then</b>,
		<b>While</b> the top meta-operation on the operation stack is not a left parenthesis <b>do</b>,
			Pop the operation from the operation stack.
			Append that operation to the postfix queue.
		<b>If</b> the operation stack is empty <b>then</b>,
			<b>Exception</b> “Right parenthesis, has no matching left parenthesis”
		Pop the left parenthesis from the operation stack.
		<b>If</b> the top of the operation stack is a function <b>then</b>,
			Pop the function from the operation stack
			Append that function to the postfix queue.
	<b>Else if</b> the token is an operator <b>then</b>,
		<b>While</b> the operation stack is not empty <b>do</b>
			<b>If</b> the top of the operation stack is not an operator <b>then</b>,
				<b>Exit</b> the while loop.
			<b>If</b> the token is a non-associative operator <b>then</b>,
				<b>Exit</b> the while loop.
			<b>If</b> the token is a left-associative operator <b>and</b> 
			has greater precedence than the top of the operation stack <b>then</b>,
				<b>Exit</b> the while loop.
			<b>If</b> the token is a right-associative operator <b>and</b> 
				has greater or equal precedence than the top of the operation stack <b>then</b>,
				<b>Exit</b> the while loop.
            Pop an operator from the top of the operation stack.
			Append that operator to the postfix queue.
		<b>End while</b>
		Push the token on to the operation stack.
	<b>Else</b>
		<b>Exception</b> “Unknown token”.
<b>End for-each</b>
<b>While</b> the operation stack is not empty <b>do</b>
	<b>If</b> the top of the operation stack is a left-parenthesis <b>then</b>,
		<b>Exception</b> “Missing right-parenthesis”.
	Pop an operator from the top of the operation stack.
	Append that operator to the postfix queue.
<b>Return</b> postfix queue
</pre>

## Architecture

![Sequence Diagram](!docs/Sequence%20Diagram.jpg)