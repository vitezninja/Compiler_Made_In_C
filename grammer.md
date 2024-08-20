# Grammer

```ebnf
<program> ::= <global_declaration>* "TOKEN_EOF"

<global_declaration> ::= <global_variable_declaration>
                      |  <function_declaration>

<global_variable_declaration> ::= <type> "TOKEN_IDENTIFIER" ("TOKEN_EQUALS" <expression>)? "TOKEN_SEMICOLON"

<local_variable_declaration> ::= <type> "TOKEN_IDENTIFIER" ("TOKEN_EQUALS" <expression>)? "TOKEN_SEMICOLON"

<function_declaration> ::= <type> "TOKEN_IDENTIFIER" "TOKEN_OPEN_PARENTHESIS" <parameter_list> "TOKEN_CLOSE_PARENTHESIS" <compound_statement>

<parameter_list> ::= <parameter> ("TOKEN_COMMA" <parameter_list>)*

<parameter> ::= <type> "TOKEN_IDENTIFIER"

<type> ::= "TOKEN_KEYWORD"[int, float, char, string, void]

<compound_statement> ::= "TOKEN_OPEN_CURLY" <statement_list> "TOKEN_CLOSE_CURLY"

<statement_list> ::= <statement>+

<statement> ::= <expression_statement> 
             |  <selection_statement> 
             |  <iteration_statement>
             |  <return_statement>
             |  <compound_statement>

<expression_statement> ::= <expression>? "TOKEN_SEMICOLON"

<selection_statement> ::= "TOKEN_KEYWORD"[if] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement> 
                       |  "TOKEN_KEYWORD"[if] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement> "TOKEN_KEYWORD"[else] <statement>

<iteration_statement> ::= <for_iteration_statement>
                       |  <while_iteration_statement>
                       |  <do_iteration_statement>

<for_iteration_statement> ::= "TOKEN_KEYWORD"[for] "TOKEN_OPEN_PARENTHESIS" <expression_statement> <expression_statement> <expression>? "TOKEN_CLOSE_PARENTHESIS" <statement>

<while_iteration_statement> ::= "TOKEN_KEYWORD"[while] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" <statement>

<do_iteration_statement> ::= "TOKEN_KEYWORD"[do] <statement> "TOKEN_KEYWORD"[while] "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS" 

<return_statement> ::= "TOKEN_KEYWORD"[return] <expression_statement>

<expression> ::= <local_variable_declaration>
              |  <binary_expression>

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

<unary_expression> ::= <primary_expression>
                    |  <prefix_unary_token> <unary_expression>
                    |  <unary_expression> <postfix_unary_token>

<prefix_unary_token> ::= "TOKEN_PLUS"
                      |  "TOKEN_MINUS"
                      |  "TOKEN_NOT"
                      |  "TOKEN_BITWISE_NOT"

<postfix_unary_token> ::= ε

<primary_expression> ::= "TOKEN_IDENTIFIER"
                      |  <literal>
                      |  "TOKEN_OPEN_PARENTHESIS" <expression> "TOKEN_CLOSE_PARENTHESIS"

<literal> ::= "TOKEN_INTEGER"
           |  "TOKEN_FLOATINGPOINT"
           |  "TOKEN_CHARACTER"
           |  "TOKEN_STRING"
```

This doenst show precedence correctly