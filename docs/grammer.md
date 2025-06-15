# Language syntax:

## Keywords:
```
{types}
typedef
const
ptr
const_ptr
if
else
endif
switch
case
default
for
foreach
while
do
return
continue
break
goto
when
struct
union
enum
sizeof
typeof
import
from
export
```

## Operators:
```
+   &    &&   +=   &=    =   ==   (   )
-   |    ||   -=   |=    <   <=   [   ]
*   ^    ++   *=   ^=    >   >=   {   }
/   <<   --   /=   <<=   !   !=   ,   ;
%   >>        %=   >>=   ~   .    :
```

```ebnf
Assignment_operators = "="
                     | "+=" 
                     | "-="
                     | "*="
                     | "/=" 
                     | "%=" 
                     | "&=" 
                     | "|="
                     | "^="
                     | "<<="
                     | ">>=" ;

Binary_operators = "&" 
                 | "|"
                 | "^"
                 | "&&"
                 | "||" ;

Equality_operator = "==" 
                  | "!=" ;

Relational_operator = "<"
                    | ">" 
                    | "<="
                    | ">=" ;

Shift_operator = "<<"
               | ">>" ;

Additive_operator = "+"
                  | "-" ;

Multiplicative_operator = "*"
                        | "/"
                        | "%" ;

Unary_operators = "-"
                | "*"
                | "&"
                | "!" 
                | "~" ;

Prefix_operators = "++" 
                 | "--" ;

Postfix_operators = "++" 
                  | "--"
                  | ( "." identifier ) ;

```

## Types:
```ebnf
Type = "int64"   | "int32"   | "int16"  | "int8"
     | "uint64"  | "uint32"  | "uint16" | "uint8"
     | "float64" | "float32"
     | "char"    | "string"
     | "bool"
     | "void" 
     | identifier
     | ( ( "struct" | "union" | "enum" ) identifier ) ;
```

## Type specifiers:
```ebnf
Type_specifiers = ( const { ( const_ptr | ptr ) } )
               | ( ( const_ptr | ptr ) { ( const_ptr | ptr ) } )  ;
```

## Full Type
```ebnf
Full_type = [ Type_specifiers ] Type ;
```

## Escape characters
```ebnf
Escape_characters = "\a" 
                 | "\b"
                 | "\f"
                 | "\n"
                 | "\r"
                 | "\t"
                 | "\v"
                 | "\\"
                 | "\'"
                 | "\"" ;
```

## Literals:
```ebnf
Literal = Integer_literal | Binary_literal | Octal_literal | Hexadecimal_literal
        | Floating-point_literal
        | Character_literal
        | String_literal
        | Boolean_literal
        | Null_literal ;

Decimal_digits_no_zero     = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
Binary_digits_no_zero      = "1" ;
Octal_digits_no_zero       = "1" | "2" | "3" | "4" | "5" | "6" | "7" ;
Hexadecimal_digits_no_zero = Decimal_digits_no_zero | "a" | "A" | "b" | "B" | "c" | "C" | "d" | "D" | "e" | "E" | "f" | "F" ;

Decimal_digits         = "0" | Decimal_digits_no_zero ;
Binary_digits          = "0" | Binary_digits_no_zero ;
Octal_digits           = "0" | Octal_digits_no_zero ;
Hexadecimal_digits     = "0" | Hexadecimal_digits_no_zero ;

Characters = /* All ASCII characters from 65 to 90 and 97 to 122 */

Integer_literal        = "0" | ( Decimal_digits_no_zero { Decimal_digits } ) ;
Binary_literal         = "0" ( "b" | "B" ) Binary_digits_no_zero { Binary_digits } ;
Octal_literal          = "0" ( "o" | "O" ) Octal_digits_no_zero { Octal_digits } ;
Hexadecimal_literal    = "0" ( "x" | "X" ) Hexadecimal_digits_no_zero { Hexadecimal_digits } ;
Floating-point_literal = Integer_literal "," Integer_literal ;
Character_literal      = "'" ( Characters | Escape_characters ) "'";
String_literal         = """ { ( Characters | Escape_characters ) } """;
Boolean_literal        = "true" | "false" ;
Null_literal           = "null" | "NULL" ;
```

## Program
```ebnf
Program = { Import } { ( Function_declaration | Global_variables_declaration | Struct_declaration | Union_declaration | Enum_declaration | Typedef ) } end_of_file ;
```

## Importing
```ebnf
Import = ( "import" String_literal ) 
       | ( "import" Identifier_list "from" String_literal ) ;

Identifier_list = identifier { "," identifier } ;
```

## Functions
```ebnf
Function_declaration = [ "export" ] "(" Return_parameter_list ")" identifier "(" [ Function_parameter_list ] ")" Compound_statement ;

Return_parameter_list = Full_type { "," Full_type } ;

Function_parameter_list = Function_parameter { "," Function_parameter } ;

Function_parameter = Full_type identifier ;
```

## Global variables
```ebnf
Global_variables_declaration = [ "export" ] Full_type identifier { "," [ "export" ] Full_type identifier } [ "=" Expression ] ";" ;
```

## Stucts, Unions and Enums
```ebnf
Struct_declaration = [ "export" ] "struct" identifier "{" Struct_Union_member_declaration "}" ;

Union_declaration = [ "export" ] "union" identifier "{" Struct_Union_member_declaration "}" ;

Struct_Union_member_declaration = Full_type identifier ";" { Full_type identifier ";" } ;

Struct_Union_declarator = "{" ( Struct_Union_indirect_declarator | Struct_Union_direct_declarator ) "}" ;

Struct_Union_indirect_declarator = Expression { "," Expression } ;

Struct_Union_direct_declarator = "." identifier "=" Expression { "," "." identifier "=" Expression } ;

Enum_declaration = [ "export" ] "enum" identifier "{" Enum_value_declaration "}" ;

Enum_value_declaration = identifier [ "=" Expression ] "," { identifier [ "=" Expression ] "," } ;
```

## Own types
```ebnf
Typedef = [ "export" ] "typedef" Full_type identifier ;
```

## Statements:
```ebnf
Statement = Branch_statement | Loop_statement | Compound_statement | Jump_statement | Expression_statement ;
```

### Branch statements:
```ebnf
Branch_statement = If_statement | Switch_statement ;

If_statement = "if" "(" Expression ")" Statement [ "else" Statement ] "endif" ;

Switch_statement = "switch" "(" Expression ")" "{" Switch_Case { Case_statement } [ Switch_Default ] "}" ;

Switch_Case = "case" Expression ":" Statement ;

Switch_Default = "default" ":" Statement ;
```

### Loop statements:
```ebnf
Loop_statement = For_statement | Foreach_statement | While_statement | Do_while_statement ;

For_statement = "for" "(" [ For_initializer ] ";" [ For_condition ] ";" [ For_incrementation ] ")" Statement ;

For_initializer = Assignment | Variable_declaration ;

For_condition = Expression ;

For_incrementation = Expression ;

Foreach_statement = "foreach" "(" Full_type identifier ":" identifier ")" Statement ;

While_statement = "while" "(" Expression ")" Statement ;

Do_while_statement = "do" Statement "while" "(" Expression ")" ";" ;
```

### Other statements:
```ebnf
Compound_statement = "{" { Statement | Label } "}";

Label = identifier ":" ;

Expression_statement = ( Expression ";" )
                     | ( Variable_declaration ";" ) 
                     | ";" ;
```

#### Variable declaration:
```ebnf
Variable_declaration = Full_type identifier { "," Full_type identifier } [ "=" Expression ] ;
```

### Control flow statements:
```ebnf
Jump_statement = Goto_statement | Return_statement | Break_statement | Continue_statement ;

Goto_statement = "goto" identifier [ "when" "(" Expression ")" ] ";" ;

Return_statement = "return" [ Expression ] ";" ;

Break_statement = "break" ";" ;

Continue_statement = "continue" ";" ;
```

## Expressions
```ebnf
Expression = Assignment_expression ;

Assignment_expression = ( Logical_OR_expression )
                      | ( Unary_expression { "," Unary_expression } Assignment_operators Expression ) ;

Logical_OR_expression = Logical_AND_expression { "||" Logical_AND_expression } ;

Logical_AND_expression = Bitwise_OR_expression { "&&" Bitwise_OR_expression } ;

Bitwise_OR_expression = Bitwise_XOR_expression { "|" Bitwise_XOR_expression } ;

Bitwise_XOR_expression = Bitwise_AND_expression { "^" Bitwise_AND_expression } ;

Bitwise_AND_expression = Equality_expression { "&" Equality_expression } ;

Equality_expression = Relational_expression { Equality_operator Relational_expression } ;

Relational_expression = Shift_expression { Relational_operator Shift_expression } ;

Shift_expression = Additive_expression { Shift_operator Additive_expression } ;

Additive_expression = Multiplicative_expression { Additive_operator Multiplicative_expression } ;

Multiplicative_expression = Unary_expression { Multiplicative_operator Unary_expression } ;

Unary_expression = ( Prefix_operator Unary_expression ) 
                 | ( Unary_operator Type_cast_expression ) 
                 | Type_cast_expression ;

Type_cast_expression = ( "(" Full_type ")" Type_cast_expression )
                     | Postfix_expression ;

Postfix_expression = Struct_Union_declarator
                   | ( Primary_expression { Postfix_prime_expression } ) ;

Postfix_prime_expression = Postfix_operator
                         | Array_indexing_expression
                         | Function_call_expression ;

Array_indexing_expression = "[" Expression "]" ;

Function_call_expression = "(" [ Expression { "," Expression } ] ")" ;

Primary_expression = identifier 
                   | Literal 
                   | ( "(" Expression ")" );
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
            <td rowspan="5">14</td>
            <td>++, --</td>
            <td>Postfix Increment and decrement operators.</td>
            <td rowspan="5">Left-to-right</td>
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
            <td>(type){list}</td>
            <td>Compound literal.</td>
        </tr>
        <tr>
            <td rowspan="6">13</td>
            <td>++, --</td>
            <td>Prefix Increment and decrement operators.</td>
            <td rowspan="6">Right-to-left</td>
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
            <td>12</td>
            <td>*, /, %</td>
            <td>Multiplication, division, and remainder.</td>
            <td rowspan="10">Left-to-right</td>
        </tr>
        <tr>
            <td>11</td>
            <td>+, -</td>
            <td>Addition and subtraction.</td>
        </tr>
        <tr>
            <td>10</td>
            <td>&lt;&lt;, &gt;&gt;</td>
            <td>Bitwise shift left and right.</td>
        </tr>
        <tr>
            <td>9</td>
            <td>&lt;, &lt;=, &gt;, &gt;=</td>
            <td>Less than, less than or equal, greater than, greater than or equal.</td>
        </tr>
        <tr>
            <td>8</td>
            <td>==, !=</td>
            <td>Equality and inequality comparison.</td>
        </tr>
        <tr>
            <td>7</td>
            <td>&amp;</td>
            <td>Bitwise AND.</td>
        </tr>
        <tr>
            <td>6</td>
            <td>^</td>
            <td>Bitwise XOR.</td>
        </tr>
        <tr>
            <td>5</td>
            <td>|</td>
            <td>Bitwise OR.</td>
        </tr>
        <tr>
            <td>4</td>
            <td>&&</td>
            <td>Logical AND.</td>
        </tr>
        <tr>
            <td>3</td>
            <td>||</td>
            <td>Logical OR.</td>
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