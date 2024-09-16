# Grammar

```ebnf
<program> ::= <global_declaration>* "TOKEN_EOF"


<global_declaration> ::= <function_definition> | <declaration>


<function_definition> ::= <declaration_specifiers> <declarator> <declaration>* <compound_statement>


<declaration_specifiers> ::= (<storage_class_specifier> | <specifier_qualifier> | "TOKEN_KEYWORD"[inline])+


<storage_class_specifier> ::= "TOKEN_KEYWORD"[typedef]
                           |  "TOKEN_KEYWORD"[extern]
                           |  "TOKEN_KEYWORD"[static]
                           |  "TOKEN_KEYWORD"[auto]
                           |  "TOKEN_KEYWORD"[register]


<type_specifier> ::= <struct_or_union_specifier>
                  |  <enum_specifier>
                  |  "TOKEN_IDENTIFIER"
                  |  "TOKEN_KEYWORD"[void]
                  |  "TOKEN_KEYWORD"[char]
                  |  "TOKEN_KEYWORD"[short]
                  |  "TOKEN_KEYWORD"[int]
                  |  "TOKEN_KEYWORD"[long]
                  |  "TOKEN_KEYWORD"[float]
                  |  "TOKEN_KEYWORD"[double]
                  |  "TOKEN_KEYWORD"[signed]
                  |  "TOKEN_KEYWORD"[unsigned]
                  |  "TOKEN_KEYWORD"[string]


<struct_or_union_specifier> ::= ("TOKEN_KEYWORD"[struct] | "TOKEN_KEYWORD"[union]) "TOKEN_IDENTIFIER"? "TOKEN_OPEN_CURLY" <struct_declaration>+ "TOKEN_CLOSE_CURLY"
                             |  ("TOKEN_KEYWORD"[struct] | "TOKEN_KEYWORD"[union]) "TOKEN_IDENTIFIER"

<struct_declaration> ::= <specifier_qualifier>+ <struct_declarator_list> "TOKEN_SEMICOLON"


<specifier_qualifier> ::= <type_specifier>
                       |  <type_qualifier>


<type_qualifier> ::= "TOKEN_KEYWORD"[const]
                  |  "TOKEN_KEYWORD"[restrict]
                  |  "TOKEN_KEYWORD"[volatile]


<struct_declarator_list> ::= <struct_declarator> ("TOKEN_COMMA" <struct_declarator>)*

<struct_declarator> ::= <declarator>
                     |  <declarator>? "TOKEN_COLON" <constant_expression>


<declarator> ::= <pointer>? <direct_declarator>


<pointer> ::= ("TOKEN_STAR" <type_qualifier>*)+


<direct_declarator> ::= "TOKEN_IDENTIFIER" <direct_declarator_prime>*
                     |  "TOKEN_OPEN_PARENTHESIS" <declarator> "TOKEN_CLOSED_PARENTHESIS" <direct_declarator_prime>*

<direct_declarator_prime> ::= "TOKEN_OPEN_BRACKET" "TOKEN_KEYWORD"[static] <type_qualifier>* <assignment_expression> "TOKEN_CLOSED_BRACKET"
	                       |  "TOKEN_OPEN_BRACKET" <type_qualifier>+ "TOKEN_KEYWORD"[static] <assignment_expression> "TOKEN_CLOSED_BRACKET"
                           |  "TOKEN_OPEN_BRACKET" <type_qualifier>* "TOKEN_STAR" "TOKEN_CLOSED_BRACKET"
                           |  "TOKEN_OPEN_BRACKET" <type_qualifier>* <assignment_expression>? "TOKEN_CLOSED_BRACKET"
	                       |  "TOKEN_OPEN_PARENTHESIS" <parameter_list> "TOKEN_CLOSED_PARENTHESIS"
	                       |  "TOKEN_OPEN_PARENTHESIS" <identifier_list>? "TOKEN_CLOSED_PARENTHESIS"

<assignment_expression> ::= <constant_expression>
                         |  <unary_expression> <assignment_operator> <assignment_expression>

<assignment_operator> ::= "TOKEN_EQUALS"
                       |  "TOKEN_STAR_EQUAL"
                       |  "TOKEN_SLASH_EQUAL"
                       |  "TOKEN_PERCENT_EQUAL"
                       |  "TOKEN_PLUS_EQUAL"
                       |  "TOKEN_MINUS_EQUAL"
                       |  "TOKEN_BITWISE_LEFT_SHIFT_EQUAL"
                       |  "TOKEN_BITWISE_RIGHT_SHIFT_EQUAL"
                       |  "TOKEN_BITWISE_AND_EQUAL"
                       |  "TOKEN_BITWISE_XOR_EQUAL"
                       |  "TOKEN_BITWISE_OR_EQUAL"


<constant_expression> ::= <conditional_expression>


<conditional_expression> ::= <logical_OR_expression>
                          |  <logical_OR_expression> "TOKEN_QUESTION_MARK" <expression> "TOKEN_COLON" <conditional_expression>


<logical_OR_expression> ::= <logical_AND_expression> ("TOKEN_OR" <logical_AND_expression>)*


<logical_AND_expression> ::= <bitwise_OR_expression> ("TOKEN_AND" <bitwise_OR_expression>)*


<bitwise_OR_expression> ::= <bitwise_XOR_expression> ("TOKEN_BITWISE_OR" <bitwise_XOR_expression>)*


<bitwise_XOR_expression> ::= <bitwise_AND_expression> ("TOKEN_BITWISE_XOR" <bitwise_AND_expression>)*


<bitwise_AND_expression> ::= <equality_expression> ("TOKEN_BITWISE_AND" <equality_expression>)*


<equality_expression> ::= <relational_expression> (<equality_operator> <relational_expression>)*

<equality_operator> ::= "TOKEN_DOUBLE_EQUALS"
                     |  "TOKEN_NOT_EQUALS"


<relational_expression> ::= <shift_expression> (<relational_operator> <shift_expression>)*

<relational_operator> ::= "TOKEN_LESS_THAN"
                       |  "TOKEN_LESS_THAN_OR_EQUAL"
                       |  "TOKEN_GREATER_THAN"
                       |  "TOKEN_GREATER_THAN_OR_EQUAL"


<shift_expression> ::= <additive_expression> (<shift_operator> <additive_expression>)*

<shift_operator> ::= "TOKEN_BITWISE_LEFT_SHIFT"
                  |  "TOKEN_BITWISE_RIGHT_SHIFT"


<additive_expression> ::= <multiplicative_expression> (<additive_operator> <multiplicative_expression>)*

<additive_operator> ::= "TOKEN_PLUS"
                     |  "TOKEN_MINUS"


<multiplicative_expression> ::= <cast_expression> (<multiplicative_operator> <cast_expression>)*

<multiplicative_operator> ::= "TOKEN_STAR"
                           |  "TOKEN_SLASH"
                           |  "TOKEN_PERCENT"


<cast_expression> ::= <unary_expression>
                   |  "TOKEN_OPEN_PARENTHESIS" <type_name> "TOKEN_CLOSE_PARENTHESIS" <cast_expression>


<unary_expression> ::= <postfix_expression>
                    |  <prefix_unary_token> <unary_expression>
                    |  <unary_operator> <cast_expression>
                    |  "TOKEN_KEYWORD"[sizeof] <unary_expression>
                    |  "TOKEN_KEYWORD"[sizeof] "TOKEN_OPEN_PARENTHESIS" <type_name> "TOKEN_CLOSE_PARENTHESIS"

<unary_operator> ::= "TOKEN_BITWISE_AND"
                  |  "TOKEN_STAR"
                  |  "TOKEN_PLUS"
                  |  "TOKEN_MINUS"
                  |  "TOKEN_BITWISE_NOT"
                  |  "TOKEN_NOT"

<prefix_unary_token> ::= "TOKEN_DOUBLE_PLUS"
                      |  "TOKEN_DOUBLE_MINUS"


<postfix_expression> ::= <primary_expression> <postfix_expression_prime>*
                      |  "TOKEN_OPEN_PARENTHESIS" <type_name> "TOKEN_CLOSE_PARENTHESIS" "TOKEN_OPEN_CURLY" <initializer_list> "TOKEN_COLON"? "TOKEN_CLOSE_CURLY" <postfix_expression_prime>*

<postfix_expression_prime> ::= "TOKEN_OPEN_BRACKET" <expression> "TOKEN_CLOSED_BRACKET"
                            |  "TOKEN_OPEN_PARENTHESIS" <expression>? "TOKEN_CLOSE_PARENTHESIS"
                            |  <postfix_operator>

<postfix_operator> ::= "TOKEN_DOT" "TOKEN_IDENTIFIER"
                    |  "TOKEN_ARROW" "TOKEN_IDENTIFIER"
                    |  "TOKEN_DOUBLE_PLUS"
                    |  "TOKEN_DOUBLE_MINUS"


<primary_expression> ::= "TOKEN_IDENTIFIER"
                      |  <literal>
                      |  "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS"


<literal> ::= "TOKEN_INTEGER"
           |  "TOKEN_FLOATINGPOINT"
           |  "TOKEN_CHARACTER"
           |  "TOKEN_STRING"
           |  "TOKEN_HEXADECIMAL"
           |  "TOKEN_OCTAL"


<expression> ::= <assignment_expression> ("TOKEN_COMMA" <assignment_expression>)*


<argument_expression> ::= <assignment_expression> ("TOKEN_COMMA" <assignment_expression>)*


<type_name> ::= <specifier_qualifier>+ <abstract_declarator>?


<abstract_declarator> ::= <pointer>
                       |  <pointer>? <direct_abstract_declarator>


<direct_abstract_declarator> ::= "TOKEN_OPEN_PARENTHESIS" <abstract_declarator> "TOKEN_CLOSE_PARENTHESIS" <direct_abstract_declarator_prime>*

<direct_abstract_declarator_prime> ::= "TOKEN_OPEN_PARENTHESIS" <parameter_list>? "TOKEN_CLOSE_PARENTHESIS"
                                    |  "TOKEN_OPEN_BRACKET" "TOKEN_STAR" "TOKEN_CLOSED_BRACKET"
                                    |  "TOKEN_OPEN_BRACKET" <assignment_expression>? "TOKEN_CLOSED_BRACKET"

<parameter_list> ::= <parameter_declaration> ("TOKEN_COMMA" <parameter_declaration>)*


<parameter_declaration> ::= <declaration_specifiers> <declarator>
                         |  <declaration_specifiers> <abstract_declarator>?


<initializer_list> ::= <designation>? <initializer> ("TOKEN_COMMA" <designation>? <initializer>)*


<designation> ::= <designator>+ "TOKEN_EQUALS"


<designator> ::= "TOKEN_OPEN_BRACKET" <constant_expression> "TOKEN_CLOSED_BRACKET"
              |  "TOKEN_DOT" "TOKEN_IDENTIFIER"


<initializer> ::= <assignment_expression>
               |  "TOKEN_OPEN_CURLY" <initializer_list> "TOKEN_COLON"? "TOKEN_CLOSE_CURLY"


<identifier_list> ::= "TOKEN_IDENTIFIER" ("TOKEN_COMMA", "TOKEN_IDENTIFIER")*


<enum_specifier> ::= "TOKEN_KEYWORD"[enum] "TOKEN_IDENTIFIER"
                  |  "TOKEN_KEYWORD"[enum] "TOKEN_IDENTIFIER"? "TOKEN_OPEN_CURLY" <enumerator_list> "TOKEN_COMMA"? "TOKEN_CLOSE_CURLY"

<enumerator_list> ::= <enumerator> ("TOKEN_COMMA" <enumerator>)*

<enumerator> ::= "TOKEN_IDENTIFIER" ("TOKEN_EQUALS" <constant_expression>)?


<declaration> ::= <declaration_specifiers> <init_declarator_list>? "TOKEN_SEMICOLON"


<init_declarator_list> ::= <init_declarator> ("TOKEN_COMMA" <init_declarator>)*

<init_declarator> ::= <declarator> ("TOKEN_EQUALS" <initializer>)?


<statement> ::= <labeled_statement>
             |  <compound_statement>
             |  <expression_statement> 
             |  <selection_statement> 
             |  <iteration_statement>
             |  <jump_statement>


<labeled_statement> ::= "TOKEN_IDENTIFIER" "TOKEN_COLON" <statement>
                     |  "TOKEN_KEYWORD"[case] <constant_expression> "TOKEN_COLON" <statement>
                     |  "TOKEN_KEYWORD"[default] "TOKEN_COLON" <statement>


<compound_statement> ::= "TOKEN_OPEN_CURLY" (<declaration> | <statement>)* "TOKEN_CLOSE_CURLY"


<expression_statement> ::= <expression>? "TOKEN_SEMICOLON"


<selection_statement> ::= "TOKEN_KEYWORD"[if] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement>
                       |  "TOKEN_KEYWORD"[if] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement> "TOKEN_KEYWORD"[else] <statement>
                       |  "TOKEN_KEYWORD"[switch] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement>


<iteration_statement> ::= "TOKEN_KEYWORD"[for] "TOKEN_OPEN_PARENTHESIS" <for_control> "TOKEN_CLOSE_PARENTHESIS" <statement>
                       |  "TOKEN_KEYWORD"[while] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement>
                       |  "TOKEN_KEYWORD"[do] <statement> "TOKEN_KEYWORD"[while] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" "TOKEN_SEMICOLON"


<for_control> ::= <declaration> <expression>? "TOKEN_SEMICOLON" <expression>?
               |  <expression>? "TOKEN_SEMICOLON" <expression>? "TOKEN_SEMICOLON" <expression>?


<jump_statement> ::= "TOKEN_KEYWORD"[goto] "TOKEN_IDENTIFIER" "TOKEN_SEMICOLON"
                  |  "TOKEN_KEYWORD"[continue] "TOKEN_SEMICOLON"
                  |  "TOKEN_KEYWORD"[break] "TOKEN_SEMICOLON"
                  |  "TOKEN_KEYWORD"[return] <expression>? "TOKEN_SEMICOLON"
```

## Operator precedence

<table>
    <thead>
        <tr>
            <th>Precedence</th>
            <th>Operator Symbol</th>
            <th>Description</th>
            <th>Associativity</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="6">15</td>
            <td>++, --</td>
            <td>Postfix Increment and decrement operators.</td>
            <td rowspan="6">Left-to-right</td>
        </tr>
        <tr>
            <td>( )</td>
            <td>Function call.</td>
        </tr>
        <tr>
            <td>[ ]</td>
            <td>Array subscripting.</td>
        </tr>
        <tr>
            <td>.</td>
            <td>Structure and union member access.</td>
        </tr>
        <tr>
            <td>-></td>
            <td>Structure and union member access through pointer.</td>
        </tr>
        <tr>
            <td>(type){list}</td>
            <td>Compound literal.</td>
        </tr>
        <tr>
            <td rowspan="7">14</td>
            <td>++, --</td>
            <td>Prefix Increment and decrement operators.</td>
            <td rowspan="7">Right-to-left</td>
        </tr>
        <tr>
            <td>+, -</td>
            <td>Unary plus, and minus operators.</td>
        </tr>
        <tr>
            <td>!, ~</td>
            <td>Logical NOT and bitwise NOT operators.</td>
        </tr>
        <tr>
            <td>(type)</td>
            <td>Type cast.</td>
        </tr>
        <tr>
            <td>*</td>
            <td>Indirection dereference.</td>
        </tr>
        <tr>
            <td>&</td>
            <td>Address-of.</td>
        </tr>
        <tr>
            <td>sizeof</td>
            <td>Size-of.</td>
        </tr>
        <tr>
            <td rowspan="1">13</td>
            <td>*, /, %</td>
            <td>Multiplication, division, and remainder.</td>
            <td rowspan="10">Left-to-right</td>
        </tr>
        <tr>
            <td rowspan="1">12</td>
            <td>+, -</td>
            <td>Addition and subtraction.</td>
        </tr>
        <tr>
            <td>11</td>
            <td>&lt;&lt;, &gt;&gt;</td>
            <td>Bitwise shift left and right.</td>
        </tr>
        <tr>
            <td>10</td>
            <td>&lt;, &lt;=, &gt;, &gt;=</td>
            <td>Less than, less than or equal, greater than, greater than or equal.</td>
        </tr>
        <tr>
            <td>9</td>
            <td>==, !=</td>
            <td>Equality and inequality comparison.</td>
        </tr>
        <tr>
            <td>8</td>
            <td>&amp;</td>
            <td>Bitwise AND.</td>
        </tr>
        <tr>
            <td>7</td>
            <td>^</td>
            <td>Bitwise XOR.</td>
        </tr>
        <tr>
            <td>6</td>
            <td>|</td>
            <td>Bitwise OR.</td>
        </tr>
        <tr>
            <td>5</td>
            <td>&&</td>
            <td>Logical AND.</td>
        </tr>
        <tr>
            <td>4</td>
            <td>||</td>
            <td>Logical OR.</td>
        </tr>
        <tr>
            <td>3</td>
            <td>? :</td>
            <td>Ternary conditional.</td>
            <td rowspan="5">Right-to-left</td>
        </tr>
        <tr>
            <td rowspan="5">2</td>
            <td>=</td>
            <td>Simple assignment.</td>
        </tr>
        <tr>
            <td>+=, -=</td>
            <td>Assignment by sum and difference.</td>
        </tr>
        <tr>
            <td>*=, /=, %=</td>
            <td>Assignment by product, quotient, and remainder.</td>
        </tr>
        <tr>
            <td><<=, =>></td>
            <td>Assignment by bitwise left shift and right shift.</td>
        </tr>
        <tr>
            <td>&=, ^=, |=</td>
            <td>Assignment by bitwise AND, XOR, and OR.</td>
        </tr>
        <tr>
            <td>1</td>
            <td>,</td>
            <td>Comma.</td>
            <td>Left-to-right</td>
        </tr>
    </tbody>
</table>

### How to Read the Operator Precedence Table

Operator precedence determines the order in which operations are performed in an expression.

1. **Lower Precedence Numbers Mean Stronger Binding**: Operators with higher precedence numbers are evaluated before those with lower numbers. For example, multiplication (`*`) has a stronger binding than addition (`+`), so in the expression `3 + 4 * 5`, the multiplication is done first.

2. **Associativity**: This indicates the direction in which operators of the same precedence are evaluated.
   - **Left-to-right**: Operators are evaluated from left to right. For example, in the expression `10 - 5 + 2`, subtraction and addition are performed from left to right.
   - **Right-to-left**: Operators are evaluated from right to left. For example, in assignments like `a = b = 5`, the assignment is done from right to left.

### Example:
- **Basic Precedence**: Consider the expression `3 + 4 * 5`. Since multiplication (`*`) has a higher precedence number than addition (`+`), `4 * 5` is evaluated first, giving `20`. Adding `3` results in `23`.

- **Unary Operators**: For the expression `-3 + 4`, the unary minus (`-`) has a higher precedence number than addition (`+`). This means the `-3` is evaluated first, and then `4` is added, resulting in `1`.

- **Operator Associativity**: For the expression `a = b = 5 + 3`, both the assignment operator (`=`) and addition operator (`+`) have different precedences. The addition operator has a higher precedence number, so `5 + 3` is evaluated first, resulting in `8`. Then, the assignments are performed from right to left, so `b` is assigned `8` first, and then `a` is also assigned `8`.

This table helps in understanding the evaluation order of operators in expressions and predicting how complex expressions will be processed.

## References

- C99 Grammar converted from [ISO/IEC 9899:1999](https://slebok.github.io/zoo/c/c99/iso-9899-1999/extracted/index.html)

- C Operator Precedence from [cppreference.com](https://en.cppreference.com/w/c/language/operator_precedence)