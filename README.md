<h1 align="left">exprevaluator</h1>

###

<p align="left">A Windows console application that evaluates mathematical expressions involving multiple operators and functions. It supports operations on a variety of data types, including Boolean, Integer, Real, and Variable.</p>

###

<h2 align="left">Features</h2>

###

<ul>
    <li>Supports various operators:
    <br><br>
        <table border="1" cellspacing="0" cellpadding="5">
            <thead>
                <tr>
                    <th>Type</th>
                    <th>Operators</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td>Unary</td>
                    <td>Negation (<code>-x</code>), Not (<code>!x</code>), Factorial (<code>x!</code>)</td>
                </tr>
                <tr>
                    <td>Arithmetic</td>
                    <td>Addition (<code>+</code>), Subtraction (<code>-</code>), Multiplication (<code>*</code>), Division (<code>/</code>), Modulus (<code>%</code>), Power (<code>**</code>)</td>
                </tr>
                <tr>
                    <td>Assignment</td>
                    <td>Assignment (<code>=</code>)</td>
                </tr>
                <tr>
                    <td>Logical</td>
                    <td>And (<code>&&</code>), Nand (<code>!&&</code>), Or (<code>||</code>), Nor (<code>!||</code>)</td>
                </tr>
                <tr>
                    <td>Relational</td>
                    <td>Equality (<code>==</code>), Inequality (<code>!=</code>), Greater (<code>&gt;</code>), GreaterEqual (<code>&gt;=</code>), Less (<code>&lt;</code>), LessEqual (<code>&lt;=</code>)</td>
                </tr>
                <tr>
                    <td>Bitwise</td>
                    <td>Xor (<code>^</code>), Xnor (<code>!^</code>)</td>
                </tr>
            </tbody>
        </table>
    </li>
    <li>Includes built-in functions
    <br><br>
        <table border="1" cellspacing="0" cellpadding="5">
            <thead>
                <tr>
                    <th>Type</th>
                    <th>Functions</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td style="white-space: nowrap;">One-Argument</td>
                    <td><code>abs</code>, <code>arccos</code>, <code>arcsin</code>, <code>arctan</code>, <code>ceil</code>, <code>cos</code>, <code>exp</code>, <code>floor</code>, <code>lb</code>, <code>ln</code>, <code>log</code>, <code>sin</code>, <code>sqrt</code>, <code>tan</code></td>
                </tr>
                <tr>
                    <td style="white-space: nowrap;">Two-Argument</td>
                    <td><code>arctan2</code>, <code>max</code>, <code>min</code>, <code>pow</code></td>
                </tr>
            </tbody>
        </table>
    </li>
    <li>Handles multiple data types: Boolean, Integer, Real, and Variable.</li>
    <li>Supports nested expressions and parentheses for complex calculations.</li>
    <li>Simple, fast, and lightweight console-based interface.</li>
</ul>

###

<h2 align="left">Architecture</h2>

###

<img src="!docs/Sequence Diagram.jpg" alt="Sequence Diagram">