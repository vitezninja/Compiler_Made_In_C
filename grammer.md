# Grammer

```ebnf
<program> ::= <global_declaration>* "TOKEN_EOF"

<global_declaration> ::= <global_variable_declaration>
                      |  <function_declaration>
                      |  <function_definition>
                      |  <type_declaration>

<global_variable_declaration> ::= <variable_declaration> ("TOKEN_EQUALS" <expression>)? "TOKEN_SEMICOLON"

<local_variable_declaration> ::= <variable_declaration> ("TOKEN_EQUALS" <expression>)? "TOKEN_SEMICOLON"

<variable_declaration> ::= <type> "TOKEN_IDENTIFIER"

<function_declaration> ::= <type> "TOKEN_IDENTIFIER" "TOKEN_OPEN_PARENTHESIS" <parameter_list> "TOKEN_CLOSE_PARENTHESIS" "TOKEN_SEMICOLON"

<function_definition> ::= <type> "TOKEN_IDENTIFIER" "TOKEN_OPEN_PARENTHESIS" <parameter_list> "TOKEN_CLOSE_PARENTHESIS" <compound_statement>

<type_declaration> ::= "TOKEN_KEYWORD"[enum] "TOKEN_IDENTIFIER"? "TOKEN_OPEN_CURLY" <enum_list> "TOKEN_CLOSE_CURLY" "TOKEN_SEMICOLON"
                    |  <type_keyword> "TOKEN_IDENTIFIER"? "TOKEN_OPEN_CURLY" <member_list> "TOKEN_CLOSE_CURLY" "TOKEN_SEMICOLON"

<type_keyword> ::= "TOKEN_KEYWORD"[struct]
                |  "TOKEN_KEYWORD"[union]

<enum_list> ::= <enum_member> ("TOKEN_COMMA" <enum_member>)* "TOKEN_COMMA"?

<enum_member> ::= "TOKEN_IDENTIFIER" ("TOKEN_EQUALS" <expression>)?

<member_list> ::= <member>+

<member> ::= <variable_declaration> "TOKEN_SEMICOLON"

<parameter_list> ::= <variable_declaration> ("TOKEN_COMMA" <variable_declaration>)*

<type_cast> ::= "TOKEN_OPEN_PARENTHESIS" <type> "TOKEN_CLOSE_PARENTHESIS"

<type> ::= "TOKEN_KEYWORD"[const]? ("TOKEN_KEYWORD"[int, float, char, string, void] | "TOKEN_IDENTIFIER")

<statement> ::= <expression_statement> 
             |  <selection_statement> 
             |  <iteration_statement>
             |  <jump_statement>
             |  <compound_statement>
             |  <labeled_statement>
             |  <local_variable_declaration>

<expression_statement> ::= <expression>? "TOKEN_SEMICOLON"

<selection_statement> ::= "TOKEN_KEYWORD"[if] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement> ("TOKEN_KEYWORD"[else] <statement>)?
                       |  "TOKEN_KEYWORD"[switch] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" "TOKEN_OPEN_CURLY" <switch_body> "TOKEN_CLOSE_CURLY"

<switch_body> ::= <case_clause>* <default_clause>? <case_clause>*

<case_clause> ::= "TOKEN_KEYWORD"[case] <literal> "TOKEN_COLON" <statement>*

<default_clause> ::= "TOKEN_KEYWORD"[default] "TOKEN_COLON" <statement>*

<iteration_statement> ::= <for_iteration_statement>
                       |  <while_iteration_statement>
                       |  <do_iteration_statement>

<for_iteration_statement> ::= "TOKEN_KEYWORD"[for] "TOKEN_OPEN_PARENTHESIS" <for_control> "TOKEN_CLOSE_PARENTHESIS" <statement>

<for_control> ::= <expression_statement> <expression_statement> <expression>?

<while_iteration_statement> ::= "TOKEN_KEYWORD"[while] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement>

<do_iteration_statement> ::= "TOKEN_KEYWORD"[do] <statement> "TOKEN_KEYWORD"[while] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" 

<jump_statement> ::= <return_statement>
                  |  <break_statement>
                  |  <continue_statement>
                  |  <goto_statement>

<return_statement> ::= "TOKEN_KEYWORD"[return] <expression_statement>

<break_statement> ::= "TOKEN_KEYWORD"[break] "TOKEN_SEMICOLON"

<continue_statement> ::= "TOKEN_KEYWORD"[continue] "TOKEN_SEMICOLON"

<compound_statement> ::= "TOKEN_OPEN_CURLY" <statement>* "TOKEN_CLOSE_CURLY"

<goto_statement> ::= "TOKEN_KEYWORD"[goto] "TOKEN_IDENTIFIER" "TOKEN_SEMICOLON"

<labeled_statement> ::= "TOKEN_IDENTIFIER" "TOKEN_COLON" <statement>

<expression> ::= <binary_expression>

<binary_expression> ::= <unary_expression>
                     |  <binary_expression> <binary_token> <binary_expression>

<binary_token> ::= "TOKEN_DOT"
                |  "TOKEN_ARROW"
                |  "TOKEN_STAR"
                |  "TOKEN_SLASH"
                |  "TOKEN_PLUS"
                |  "TOKEN_MINUS"
                |  "TOKEN_BITWISE_LEFT_SHIFT"
                |  "TOKEN_BITWISE_RIGHT_SHIFT"
                |  "TOKEN_LESS_THAN"
                |  "TOKEN_LESS_THAN_OR_EQUAL"
                |  "TOKEN_GREATER_THAN"
                |  "TOKEN_GREATER_THAN_OR_EQUAL"
                |  "TOKEN_DOUBLE_EQUALS"
                |  "TOKEN_NOT_EQUALS"
                |  "TOKEN_BITWISE_AND"
                |  "TOKEN_BITWISE_XOR"
                |  "TOKEN_BITWISE_OR"
                |  "TOKEN_AND"
                |  "TOKEN_OR"
                |  "TOKEN_EQUALS"

<unary_expression> ::= <primary_expression>
                    |  <prefix_unary_token> <unary_expression>
                    |  <unary_expression> <postfix_unary_token>

<prefix_unary_token> ::= "TOKEN_PLUS"
                      |  "TOKEN_MINUS"
                      |  "TOKEN_NOT"
                      |  "TOKEN_BITWISE_NOT"
                      |  <type_cast>? 

<postfix_unary_token> ::= ε

<primary_expression> ::= "TOKEN_IDENTIFIER"
                      |  <literal>
                      |  "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS"

<literal> ::= "TOKEN_INTEGER"
           |  "TOKEN_FLOATINGPOINT"
           |  "TOKEN_CHARACTER"
           |  "TOKEN_STRING"
```
## Operator precedence

<table>
    <thead>
        <tr>
            <th>Precedence</th>
            <th>Operator Symbol</th>
            <th>Type</th>
            <th>Description</th>
            <th>Associativity</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="3">1</td>
            <td>++, --</td>
            <td>Unary</td>
            <td>Postfix Increment and decrement operators.</td>
            <td rowspan="3">Left-to-right</td>
        </tr>
        <tr>
            <td>.</td>
            <td>Binary</td>
            <td>Structure and union member access.</td>
        </tr>
        <tr>
            <td>-></td>
            <td>Binary</td>
            <td>Structure and union member access through pointer.</td>
        </tr>
        <tr>
            <td rowspan="4">2</td>
            <td>++, --</td>
            <td>Unary</td>
            <td>Prefix Increment and decrement operators.</td>
            <td rowspan="4">Right-to-left</td>
        </tr>
        <tr>
            <td>+, -</td>
            <td>Unary</td>
            <td>Unary plus, and minus operators.</td>
        </tr>
        <tr>
            <td>!, ~</td>
            <td>Unary</td>
            <td>Logical NOT and bitwise NOT operators.</td>
        </tr>
        <tr>
            <td>(type)</td>
            <td>Unary</td>
            <td>Type cast.</td>
        </tr>
        <tr>
            <td rowspan="1">3</td>
            <td>*, /, %</td>
            <td>Binary</td>
            <td>Multiplication, division, and remainder operators.</td>
            <td rowspan="10">Left-to-right</td>
        </tr>
        <tr>
            <td rowspan="1">4</td>
            <td>+, -</td>
            <td>Binary</td>
            <td>Addition and subtraction operators.</td>
        </tr>
        <tr>
            <td>5</td>
            <td>&lt;&lt;, &gt;&gt;</td>
            <td>Binary</td>
            <td>Bitwise shift left and right operators.</td>
        </tr>
        <tr>
            <td>6</td>
            <td>&lt;, &lt;=, &gt;, &gt;=</td>
            <td>Binary</td>
            <td>Less than, less than or equal, greater than, greater than or equal operators.</td>
        </tr>
        <tr>
            <td>7</td>
            <td>==, !=</td>
            <td>Binary</td>
            <td>Equality and inequality comparison operators.</td>
        </tr>
        <tr>
            <td>8</td>
            <td>&amp;</td>
            <td>Binary</td>
            <td>Bitwise AND operator.</td>
        </tr>
        <tr>
            <td>9</td>
            <td>^</td>
            <td>Binary</td>
            <td>Bitwise XOR operator.</td>
        </tr>
        <tr>
            <td>10</td>
            <td>|</td>
            <td>Binary</td>
            <td>Bitwise OR operator.</td>
        </tr>
        <tr>
            <td>11</td>
            <td>&&</td>
            <td>Binary</td>
            <td>Logical AND operator.</td>
        </tr>
        <tr>
            <td>12</td>
            <td>||</td>
            <td>Binary</td>
            <td>Logical OR operator.</td>
        </tr>
        <tr>
            <td>13</td>
            <td>=</td>
            <td>Binary</td>
            <td>Assignment operator.</td>
            <td>Right-to-left</td>
        </tr>
    </tbody>
</table>

### How to Read the Operator Precedence Table

Operator precedence determines the order in which operations are performed in an expression.

1. **Lower Precedence Numbers Mean Stronger Binding**: Operators with lower precedence numbers are evaluated before those with higher numbers. For example, multiplication (`*`) has a stronger binding than addition (`+`), so in the expression `3 + 4 * 5`, the multiplication is done first.

2. **Associativity**: This indicates the direction in which operators of the same precedence are evaluated.
   - **Left-to-right**: Operators are evaluated from left to right. For example, in the expression `10 - 5 + 2`, subtraction and addition are performed from left to right.
   - **Right-to-left**: Operators are evaluated from right to left. For example, in assignments like `a = b = 5`, the assignment is done from right to left.

### Example:
- **Basic Precedence**: Consider the expression `3 + 4 * 5`. Since multiplication (`*`) has a lower precedence number than addition (`+`), `4 * 5` is evaluated first, giving `20`. Adding `3` results in `23`.

- **Unary Operators**: For the expression `-3 + 4`, the unary minus (`-`) has a lower precedence number than addition (`+`). This means the `-3` is evaluated first, and then `4` is added, resulting in `1`.

- **Operator Associativity**: For the expression `a = b = 5 + 3`, both the assignment operator (`=`) and addition operator (`+`) have different precedences. The addition operator has a lower precedence number, so `5 + 3` is evaluated first, resulting in `8`. Then, the assignments are performed from right to left, so `b` is assigned `8` first, and then `a` is also assigned `8`.

This table helps in understanding the evaluation order of operators in expressions and predicting how complex expressions will be processed.