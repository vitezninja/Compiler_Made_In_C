#include "parser.h"

/**
 * @brief Tries to recover from a parsing panic state.
 * 
 * This function attempts to recover the parser from a panic state by skipping tokens until it finds a valid point to continue parsing.
 * It is typically used when the parser encounters an error that prevents it from continuing normally.
 * 
 * @param parser Pointer to the Parser instance that is in a panic state.
 * 
 * @note This happens in statement parsing and program parsing.
 */
void parser_recoverPanic(Parser *parser);

/**
 * @brief Checks if the current token is a type.
 * 
 * This function checks if the current token in the parser's token list is a valid type keyword or identifier.
 * It returns true if the current token is a type, otherwise false.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return true if the current token is a type, false otherwise.
 */
bool parser_isType(Parser *parser);

/**
 * @brief Parses a type from the current token in the parser's token list.
 * 
 * This function attempts to parse a type from the current token in the parser's token list.
 * It creates a new AST node for the parsed type and returns it.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the parsed type, or NULL if parsing fails.
 */
AstNode *parser_parseType(Parser *parser);

/**
 * @brief Checks if the current token is a type specifier.
 * 
 * This function checks if the current token in the parser's token list is a valid type specifier.
 * It returns true if the current token is a type specifier, otherwise false.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return true if the current token is a type specifier, false otherwise.
 */
bool parser_isTypeSpecifier(Parser *parser);

/**
 * @brief Parses type specifiers from the current token in the parser's token list.
 * 
 * This function attempts to parse one or more type specifiers from the current token in the parser's token list.
 * It creates a new AST node for the parsed type specifiers and returns it.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the parsed type specifiers, or NULL if parsing fails.
 */
AstNode *parser_parseTypeSpecifiers(Parser *parser);

/**
 * @brief Checks if the current token is a full type.
 * 
 * This function checks if the current token in the parser's token list is a valid full type, which can include type specifiers or types.
 * It returns true if the current token is a full type, otherwise false.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return true if the current token is a full type, false otherwise.
 */
bool parser_isFullType(Parser *parser);

/**
 * @brief Parses a full type from the current token in the parser's token list.
 * 
 * This function attempts to parse a full type from the current token in the parser's token list.
 * It creates a new AST node for the parsed full type and returns it.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the parsed full type, or NULL if parsing fails.
 */
AstNode *parser_parseFullType(Parser *parser);

/**
 * @brief Checks if the current token is a literal.
 * 
 * This function checks if the current token in the parser's token list is a valid literal, such as a number, string, or character.
 * It returns true if the current token is a literal, otherwise false.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return true if the current token is a literal, false otherwise.
 */
bool parser_isLiteral(Parser *parser);

/**
 * @brief Parses a literal from the current token in the parser's token list.
 * 
 * This function attempts to parse a literal from the current token in the parser's token list.
 * It creates a new AST node for the parsed literal and returns it.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the parsed literal, or NULL if parsing fails.
 */
AstNode *parser_parseLiteral(Parser *parser);

/**
 * @brief Parses a program from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an abstract syntax tree (AST) representing the entire program.
 * It handles various constructs such as imports, function definitions, variable declarations, and more.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the root AST node representing the parsed program, or NULL if parsing fails.
 * 
 * @note This function handles panic recovery internally, allowing it to skip over errors and continue parsing the rest of the program.
 */
AstNode *parser_parseProgram(Parser *parser);

/**
 * @brief Parses an import statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an import statement.
 * It handles the syntax of import statements, which typically include the keyword "import" followed by an identifier or a string literal representing the module to be imported.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the import statement, or NULL if parsing fails.
 */
AstNode *parser_parseImport(Parser *parser);

/**
 * @brief Parses an identifier list from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a list of identifiers.
 * It handles the syntax of identifier lists, which typically include one or more identifiers separated by commas.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the identifier list, or NULL if parsing fails.
 */
AstNode *parser_parseIdentifierList(Parser *parser);

/**
 * @brief Parses a function definition from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a function definition.
 * It handles the syntax of function definitions, which typically include the return type, function name, parameter list, and function body.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the function definition, or NULL if parsing fails.
 */
AstNode *parser_parseFunctionDefinition(Parser *parser);

/**
 * @brief Parses a return parameter list from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a list of return parameters.
 * It handles the syntax of return parameter lists, which typically include one or more parameters separated by commas.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the return parameter list, or NULL if parsing fails.
 */
AstNode *parser_parseReturnParameterList(Parser *parser);

/**
 * @brief Parses a function parameter list from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a list of function parameters.
 * It handles the syntax of function parameter lists, which typically include one or more parameters separated by
 * commas and enclosed in parentheses.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the function parameter list, or NULL if parsing fails.
 */
AstNode *parser_parseFunctionParameterList(Parser *parser);

/**
 * @brief Parses a single function parameter from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a single function parameter.
 * It handles the syntax of function parameters, which typically include a type and an identifier,
 * and may also include type specifiers such as "const" or "ptr".
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the function parameter, or NULL if parsing fails.
 */
AstNode *parser_parseFunctionParameter(Parser *parser);

/**
 * @brief Parses a global variable declaration from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a global variable declaration.
 * It handles the syntax of global variable declarations, which typically include a type,
 * an identifier, and an optional initializer.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the global variable declaration, or NULL if parsing fails.
 */
AstNode *parser_parseGlobalVariableDeclaration(Parser *parser);

/**
 * @brief Parses a struct declaration from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a struct declaration.
 * It handles the syntax of struct declarations, which typically include the "struct" keyword, an identifier,
 * and a body enclosed in braces.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the struct declaration, or NULL if parsing fails.
 */
AstNode *parser_parseStructDeclaration(Parser *parser);

/**
 * @brief Parses a union declaration from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a union declaration.
 * It handles the syntax of union declarations, which typically include the "union" keyword, an identifier,
 * and a body enclosed in braces.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the union declaration, or NULL if parsing fails.
 */
AstNode *parser_parseUnionDeclaration(Parser *parser);

/**
 * @brief Parses a struct or union member declaration from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a member declaration
 * within a struct or union. It handles the syntax of member declarations, which typically include a type,
 * an identifier, and an optional initializer.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the struct or union member declaration, or NULL if parsing fails.
 */
AstNode *parser_parseStructUnionMemberDeclaration(Parser *parser);

/**
 * @brief Parses a struct or union declarator from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a declarator
 * within a struct or union. It handles the syntax of declarators, which typically include an identifier,
 * and may also include type specifiers such as "const" or "ptr".
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the struct or union declarator, or NULL if parsing fails.
 */
AstNode *parser_parseStructUnionDeclarator(Parser *parser);

/**
 * @brief Parses a struct or union indirect declarator from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an indirect declarator
 * within a struct or union. It handles the syntax of indirect declarators, which typically include an identifier,
 * and may also include type specifiers such as "const" or "ptr".
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the struct or union indirect declarator, or NULL if parsing fails.
 */
AstNode *parser_parseStructUnionIndirectDeclarator(Parser *parser);

/**
 * @brief Parses a struct or union direct declarator from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a direct declarator
 * within a struct or union. It handles the syntax of direct declarators, which typically include an identifier,
 * and may also include type specifiers such as "const" or "ptr".
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the struct or union direct declarator, or NULL if parsing fails.
 */
AstNode *parser_parseStructUnionDirectDeclarator(Parser *parser);

/**
 * @brief Parses an enum declaration from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an enum declaration.
 * It handles the syntax of enum declarations, which typically include the "enum" keyword, an identifier,
 * and a body enclosed in braces containing enum value declarations.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the enum declaration, or NULL if parsing fails.
 */
AstNode *parser_parseEnumDeclaration(Parser *parser);

/**
 * @brief Parses an enum value declaration from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an enum value declaration.
 * It handles the syntax of enum value declarations, which typically include an identifier and an optional initializer.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the enum value declaration, or NULL if parsing fails.
 */
AstNode *parser_parseEnumValueDeclaration(Parser *parser);

/**
 * @brief Parses an enum value from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an enum value.
 * It handles the syntax of enum values, which typically include an identifier and may also include an initializer.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the enum value, or NULL if parsing fails.
 */
AstNode *parser_parseEnumValue(Parser *parser);

/**
 * @brief Parses a statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a statement.
 * It handles various types of statements, including branch statements, loop statements, expression statements,
 * variable declarations, and jump statements.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the parsed statement, or NULL if parsing fails.
 * 
 * @note This function handles panic recovery internally, allowing it to skip over errors and continue parsing the rest of the statements.
 */
AstNode *parser_parseStatement(Parser *parser);

/**
 * @brief Parses a branch statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a branch statement.
 * It handles the syntax of branch statements, which typically include if statements, switch statements, and labels.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the branch statement, or NULL if parsing fails.
 */
AstNode *parser_parseBranchStatement(Parser *parser);

/**
 * @brief Parses an if statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an if statement.
 * It handles the syntax of if statements, which typically include a condition and a body, and may also include an else clause.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the if statement, or NULL if parsing fails.
 */
AstNode *parser_parseIfStatement(Parser *parser);

/**
 * @brief Parses a switch statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a switch statement.
 * It handles the syntax of switch statements, which typically include a condition and one or more case clauses.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the switch statement, or NULL if parsing fails.
 */
AstNode *parser_parseSwitchStatement(Parser *parser);

/**
 * @brief Parses a switch case from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a switch case.
 * It handles the syntax of switch cases, which typically include a case label and a body.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the switch case, or NULL if parsing fails.
 */
AstNode *parser_parseSwitchCase(Parser *parser);

/**
 * @brief Parses a switch default case from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a switch default case.
 * It handles the syntax of switch default cases, which typically include the "default" keyword and a body.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the switch default case, or NULL if parsing fails.
 */
AstNode *parser_parseSwitchDefault(Parser *parser);

/**
 * @brief Parses a loop statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a loop statement.
 * It handles various types of loop statements, including for loops, foreach loops, while loops, and do-while loops.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the loop statement, or NULL if parsing fails.
 */
AstNode *parser_parseLoopStatement(Parser *parser);

/**
 * @brief Parses a for statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a for statement.
 * It handles the syntax of for statements, which typically include an initializer, a condition, and an incrementation expression.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the for statement, or NULL if parsing fails.
 */
AstNode *parser_parseForStatement(Parser *parser);

/**
 * @brief Parses the initializer part of a for statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing the initializer
 * of a for statement. It handles the syntax of for initializers, which typically include variable declarations or assignments.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the for initializer, or NULL if parsing fails.
 */
AstNode *parser_parseForInitializer(Parser *parser);

/**
 * @brief Parses the condition part of a for statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing the condition
 * of a for statement. It handles the syntax of for conditions, which typically include a boolean expression.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the for condition, or NULL if parsing fails.
 */
AstNode *parser_parseForCondition(Parser *parser);

/**
 * @brief Parses the incrementation part of a for statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing the incrementation
 * of a for statement. It handles the syntax of for incrementation, which typically includes an expression that modifies
 * the loop variable.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the for incrementation, or NULL if parsing fails.
 */
AstNode *parser_parseForIncrementation(Parser *parser);

/**
 * @brief Parses a foreach statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a foreach statement.
 * It handles the syntax of foreach statements, which typically include a collection to iterate over and a body.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the foreach statement, or NULL if parsing fails.
 */
AstNode *parser_parseForeachStatement(Parser *parser);

/**
 * @brief Parses a while statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a while statement.
 * It handles the syntax of while statements, which typically include a condition and a body.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the while statement, or NULL if parsing fails.
 */
AstNode *parser_parseWhileStatement(Parser *parser);

/**
 * @brief Parses a do-while statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a do-while statement.
 * It handles the syntax of do-while statements, which typically include a body and a condition that is checked after the body executes.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the do-while statement, or NULL if parsing fails.
 */
AstNode *parser_parseDoWhileStatement(Parser *parser);

/**
 * @brief Parses a compound statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a compound statement.
 * It handles the syntax of compound statements, which typically include a block of code enclosed in braces.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the compound statement, or NULL if parsing fails.
 */
AstNode *parser_parseCompoundStatement(Parser *parser);

/**
 * @brief Parses a label from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a label.
 * It handles the syntax of labels, which typically include an identifier followed by a colon.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the label, or NULL if parsing fails.
 */
AstNode *parser_parseLabel(Parser *parser);

/**
 * @brief Parses an expression statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an expression statement.
 * It handles the syntax of expression statements, which typically include an expression followed by a semicolon.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the expression statement, or NULL if parsing fails.
 */
AstNode *parser_parseExpressionStatement(Parser *parser);

/**
 * @brief Parses a variable declaration from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a variable declaration.
 * It handles the syntax of variable declarations, which typically include a type, an identifier, and an optional initializer.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the variable declaration, or NULL if parsing fails.
 */
AstNode *parser_parseVariableDeclaration(Parser *parser);

/**
 * @brief Tries to parse a variable declaration from the tokens in the parser's token list.
 * 
 * This function attempts to parse a variable declaration from the current token in the parser's token list.
 * It creates a new AST node for the parsed variable declaration and returns it.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * @param success Pointer to a boolean that will be set to true if parsing succeeds, or false if it fails.
 * 
 * @return Pointer to the newly created AST node representing the variable declaration, or NULL if parsing fails.
 * 
 * @note This function does not consume parser->tokens if it fails.
 */
AstNode *parser_tryParseVariableDeclaration(Parser *parser, bool *success);

/**
 * @brief Parses a jump statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a jump statement.
 * It handles various types of jump statements, including goto statements, return statements, break statements, and continue statements.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the jump statement, or NULL if parsing fails.
 */
AstNode *parser_parseJumpStatement(Parser *parser);

/**
 * @brief Parses a goto statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a goto statement.
 * It handles the syntax of goto statements, which typically include the "goto" keyword followed by an identifier.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the goto statement, or NULL if parsing fails.
 */
AstNode *parser_parseGotoStatement(Parser *parser);

/**
 * @brief Parses a return statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a return statement.
 * It handles the syntax of return statements, which typically include the "return" keyword followed by an optional expression.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the return statement, or NULL if parsing fails.
 */
AstNode *parser_parseReturnStatement(Parser *parser);

/**
 * @brief Parses a break statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a break statement.
 * It handles the syntax of break statements, which typically include the "break" keyword followed by a semicolon.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the break statement, or NULL if parsing fails.
 */
AstNode *parser_parseBreakStatement(Parser *parser);

/**
 * @brief Parses a continue statement from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a continue statement.
 * It handles the syntax of continue statements, which typically include the "continue" keyword followed by a semicolon.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the continue statement, or NULL if parsing fails.
 */
AstNode *parser_parseContinueStatement(Parser *parser);

/**
 * @brief Parses an expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an expression.
 * It handles various types of expressions, including assignment expressions, binary expressions, unary expressions,
 * type casts, and primary expressions.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the parsed expression, or NULL if parsing fails.
 */
AstNode *parser_parseExpression(Parser *parser);

/**
 * @brief Parses an assignment expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an assignment expression.
 * It handles the syntax of assignment expressions, which typically include a left-hand side (LHS) and a right-hand side (RHS),
 * with an operator such as '=', '+=', '-=', etc.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the assignment expression, or NULL if parsing fails.
 */
AstNode *parser_parseAssignmentExpression(Parser *parser);

/**
 * @brief Parses an assignment expression starting from a unary expression node.
 * 
 * This function processes a unary expression node to construct an AST node representing an assignment expression.
 * It handles the syntax of assignment expressions, which typically include a left-hand side (LHS) and a right-hand side (RHS),
 * with an operator such as '=', '+=', '-=', etc.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * @param unaryStartNode Pointer to the unary expression node to start parsing from.
 * 
 * @return Pointer to the newly created AST node representing the assignment expression, or NULL if parsing fails.
 */
AstNode *parser_parseAssignmentExpressionFromUnary(Parser *parser, AstNode *unaryStartNode);

/**
 * @brief Gets the precedence of a given token type.
 * 
 * This function retrieves the precedence level of a specific token type.
 * It is used to determine how operators should be grouped in expressions.
 * 
 * @param type The token type for which to get the precedence.
 * 
 * @return The precedence level of the token type, or -1 if the type is not recognized.
 */
int parser_getPrecedence(My_TokenType type);

/**
 * @brief Gets the operator type for a given token type.
 * 
 * This function retrieves the operator type corresponding to a specific token type.
 * It is used to identify the kind of operation represented by the token.
 * 
 * @param type The token type for which to get the operator type.
 * 
 * @return The operator type corresponding to the token type, or AST_TYPE_UNKNOWN if the type is not recognized.
 */
AstType parser_getOperatorType(My_TokenType type);

/**
 * @brief Parses a binary expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a binary expression.
 * It handles the syntax of binary expressions, which typically include two operands and an operator between them.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * @param parentPrecedence The precedence level of the parent expression, used for operator precedence handling.
 * 
 * @return Pointer to the newly created AST node representing the binary expression, or NULL if parsing fails.
 */
AstNode *parser_parseBinaryExpression(Parser *parser, int parentPrecedence);

/**
 * @brief Parses a unary expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a unary expression.
 * It handles the syntax of unary expressions, which typically include a single operand and an operator such as '!', '-', etc.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the unary expression, or NULL if parsing fails.
 */
AstNode *parser_parseUnaryExpression(Parser *parser);

/**
 * @brief Parses a type cast expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a type cast expression.
 * It handles the syntax of type cast expressions, which typically include a type followed by an expression to be cast.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the type cast expression, or NULL if parsing fails.
 */
AstNode *parser_parseTypeCastExpression(Parser *parser);

/**
 * @brief Parses a postfix expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a postfix expression.
 * It handles the syntax of postfix expressions, which typically include an operand followed by operators such as '++', '--', etc.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the postfix expression, or NULL if parsing fails.
 */
AstNode *parser_parsePostfixExpression(Parser *parser);

/**
 * @brief Checks if the current token is a postfix prime expression.
 * 
 * This function checks if the current token in the parser's token list is a valid postfix prime expression,
 * which typically includes operators such as '++', '--', or array indexing.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return true if the current token is a postfix prime expression, false otherwise.
 */
bool parser_isPostfixPrimeExpression(Parser *parser);

/**
 * @brief Parses a postfix prime expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a postfix prime expression.
 * It handles the syntax of postfix prime expressions, which typically include operators such as '++', '--', or array indexing.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the postfix prime expression, or NULL if parsing fails.
 */
AstNode *parser_parsePostfixPrimeExpression(Parser *parser);

/**
 * @brief Parses an array indexing expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an array indexing expression.
 * It handles the syntax of array indexing, which typically includes an operand followed by square brackets containing an index expression.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the array indexing expression, or NULL if parsing fails.
 */
AstNode *parser_parseArrayIndexingExpression(Parser *parser);

/**
 * @brief Parses a function call expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a function call expression.
 * It handles the syntax of function calls, which typically include an identifier followed by parentheses containing argument expressions.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the function call expression, or NULL if parsing fails.
 */
AstNode *parser_parseFunctionCallExpression(Parser *parser);

/**
 * @brief Parses a primary expression from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a primary expression.
 * It handles the syntax of primary expressions, which typically include literals, identifiers, and parenthesized expressions.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the primary expression, or NULL if parsing fails.
 */
AstNode *parser_parsePrimaryExpression(Parser *parser);

// --------------------------------------------------------------------------------

/**
 * @brief Recovers from a panic state in the parser.
 * 
 * This function attempts to recover the parser from a panic state by skipping tokens until it finds a token
 * that can be used to continue parsing, such as a semicolon or a closing bracket.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 */
void parser_recoverSymbolPanic(Parser *parser);

/**
 * @brief Parses a program containing symbols from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a program.
 * It handles the syntax of a program, which typically includes function definitions, struct declarations,
 * global variable declarations, typedefs, enum declarations, and union declarations.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the program, or NULL if parsing fails.
 */
AstNode *parser_parseProgramSymbols(Parser *parser);

/**
 * @brief Parses a function definition symbol from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a function definition.
 * It handles the syntax of function definitions, which typically include a return type, an identifier, and a body.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the function definition, or NULL if parsing fails.
 */
AstNode *parser_parseFunctionDefinitionSymbol(Parser *parser);

/**
 * @brief Parses a struct declaration symbol from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a struct declaration.
 * It handles the syntax of struct declarations, which typically include the "struct" keyword, an identifier,
 * and a body enclosed in braces.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the struct declaration, or NULL if parsing fails.
 */
AstNode *parser_parseStructDeclarationSymbol(Parser *parser);

/**
 * @brief Parses a global variable declaration symbol from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a global variable declaration.
 * It handles the syntax of global variable declarations, which typically include a type, an identifier, and an optional initializer.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the global variable declaration, or NULL if parsing fails.
 */
AstNode *parser_parseGlobalVariableDeclarationSymbol(Parser *parser);

/**
 * @brief Parses an enum declaration symbol from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an enum declaration.
 * It handles the syntax of enum declarations, which typically include the "enum" keyword, an identifier,
 * and a body enclosed in braces containing enum value declarations.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the enum declaration, or NULL if parsing fails.
 */
AstNode *parser_parseEnumDeclarationSymbol(Parser *parser);

/**
 * @brief Parses a union declaration symbol from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing a union declaration.
 * It handles the syntax of union declarations, which typically include the "union" keyword, an identifier,
 * and a body enclosed in braces containing union member declarations.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the union declaration, or NULL if parsing fails.
 */
AstNode *parser_parseUnionDeclarationSymbol(Parser *parser);

/**
 * @brief Parses an enum value declaration symbol from the tokens in the parser's token list.
 * 
 * This function processes the tokens in the parser's token list to construct an AST node representing an enum value declaration.
 * It handles the syntax of enum value declarations, which typically include an identifier and an optional initializer.
 * 
 * @param parser Pointer to the Parser instance containing the token list.
 * 
 * @return Pointer to the newly created AST node representing the enum value declaration, or NULL if parsing fails.
 */
AstNode *parser_parseEnumValueDeclarationSymbol(Parser *parser);

// --------------------------------------------------------------------------------

void parser_recoverPanic(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_recoverPanic: Parser is NULL.\n");
        return;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_recoverPanic: No tokens available to recover from panic.\n");
        return;
    }

    while (true)
    {
        My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
        switch (currentTokenType)
        {
        case TOKEN_SEMICOLON:
        case TOKEN_CLOSE_BRACKET:
            parser->tokens = parser->tokens->next;
            parser->panic = false;
            return; // Exit recovery loop
        case TOKEN_KEYWORD_IF:
        case TOKEN_KEYWORD_ELSE:
        case TOKEN_KEYWORD_ENDIF:
        case TOKEN_KEYWORD_SWITCH:
        case TOKEN_KEYWORD_FOR:
        case TOKEN_KEYWORD_FOREACH:
        case TOKEN_KEYWORD_WHILE:
        case TOKEN_KEYWORD_DO:
        case TOKEN_KEYWORD_STRUCT:
        case TOKEN_KEYWORD_UNION:
        case TOKEN_KEYWORD_ENUM:
        case TOKEN_KEYWORD_IMPORT:
        case TOKEN_KEYWORD_EXPORT:
            parser->panic = false;
            return; // Exit recovery loop
        case TOKEN_EOF:
            DEBUG_PRINT("parser_recoverPanic: Reached EOF while recovering from panic.\n");
            return; // Exit recovery loop
        default:
            break;
        }

        parser->tokens = parser->tokens->next;
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_recoverPanic: No more tokens available for recovery.\n");
            return;
        }
    }

    UNREACHABLE();
}

bool parser_isType(Parser *parser)
{
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isType: No tokens available to check type.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    switch (currentTokenType)
    {
    case TOKEN_KEYWORD_INT_64:
    case TOKEN_KEYWORD_INT_32:
    case TOKEN_KEYWORD_INT_16:
    case TOKEN_KEYWORD_INT_8:
    case TOKEN_KEYWORD_UINT_64:
    case TOKEN_KEYWORD_UINT_32:
    case TOKEN_KEYWORD_UINT_16:
    case TOKEN_KEYWORD_UINT_8:
    case TOKEN_KEYWORD_FLOAT_64:
    case TOKEN_KEYWORD_FLOAT_32:
    case TOKEN_KEYWORD_CHAR:
    case TOKEN_KEYWORD_STRING:
    case TOKEN_KEYWORD_BOOL:
    case TOKEN_KEYWORD_VOID:
    case TOKEN_IDENTIFIER:
    case TOKEN_KEYWORD_STRUCT:
    case TOKEN_KEYWORD_UNION:
    case TOKEN_KEYWORD_ENUM:
        return true;
    default:
        return false; 
    }
    UNREACHABLE();
}

AstNode *parser_parseType(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseType: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseType: No tokens available to parse type.\n");
        return NULL;
    }

    if (!parser_isType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a type, got.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseType: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseType: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *tokens = NULL;

    Token *typeToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (typeToken == NULL)
    {
        DEBUG_PRINT("parser_parseType: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, typeToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseType: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the type token

    AstNode *typeNode = astNode_create(parser->astArena, AST_TYPE, tokens, NULL);
    if (typeNode == NULL)
    {
        DEBUG_PRINT("parser_parseType: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return typeNode;
}

bool parser_isTypeSpecifier(Parser *parser)
{
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isTypeSpecifier: No tokens available to check type specifier.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    switch (currentTokenType)
    {
    case TOKEN_KEYWORD_CONST:
    case TOKEN_KEYWORD_CONST_PTR:
    case TOKEN_KEYWORD_PTR:
        return true;    
    default:
        return false;
    }
    UNREACHABLE();
}

AstNode *parser_parseTypeSpecifiers(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseTypeSpecifiers: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypeSpecifiers: No tokens available to parse type specifiers.\n");
        return NULL;
    }

    if (!parser_isTypeSpecifier(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a type specifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        
        parser->panic = true; // Set panic state
        return NULL;
    }

    LinkedList *tokens = NULL;

    bool isFirst = true;
    while (parser_isTypeSpecifier(parser))
    {
        My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
        if (!isFirst && currentTokenType == TOKEN_KEYWORD_CONST)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Only the first type specifier can be 'const'.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseTypeSpecifiers: error_create failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseTypeSpecifiers: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic state
            return NULL;
        }

        isFirst = false;
        Token *typeSpecifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (typeSpecifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, typeSpecifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the type specifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: No tokens available after type specifier.\n");
            return NULL;
        }
    }

    AstNode *typeSpecifierNode = astNode_create(parser->astArena, AST_TYPE_SPECIFIERS, tokens, NULL);
    if (typeSpecifierNode == NULL)
    {
        DEBUG_PRINT("parser_parseTypeSpecifiers: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return typeSpecifierNode;
}

bool parser_isFullType(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_isFullType: Parser is NULL.\n");
        return false;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isFullType: No tokens available to check full type.\n");
        return false;
    }

    if (parser_isTypeSpecifier(parser) || parser_isType(parser))
    {
        return true;
    }

    return false;
}

AstNode *parser_parseFullType(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parse_fullType: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parse_fullType: No tokens available to parse full type.\n");
        return NULL;
    }

    if (!parser_isTypeSpecifier(parser) && !parser_isType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a type or type specifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parse_fullType: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parse_fullType: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state
        return NULL;
    }

    LinkedList *children = NULL;

    if (parser_isTypeSpecifier(parser))
    {
        AstNode *typeSpecifiersNode = parser_parseTypeSpecifiers(parser);
        if (typeSpecifiersNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parse_fullType: Panic state is true, skipping full type parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parse_fullType: Failed to parse type specifiers.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeSpecifiersNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parse_fullType: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parse_fullType: No tokens available after type specifiers.\n");
            return NULL;
        }
    }

    AstNode *typeNode = parser_parseType(parser);
    if (typeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parse_fullType: Panic state is true, skipping full type parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parse_fullType: Failed to parse type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parse_fullType: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parse_fullType: No tokens available after type.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_OPEN_BRACKET)
    {
        parser->tokens = parser->tokens->next; // Move past the open bracket token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parse_fullType: No tokens available after open bracket.\n");
            return NULL;
        }

        AstNode *arraySizeNode = parser_parseExpression(parser);
        if (arraySizeNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parse_fullType: Panic state is true, skipping full type parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parse_fullType: Failed to parse array size expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, arraySizeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parse_fullType: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parse_fullType: No tokens available after array size expression.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_BRACKET)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a closing bracket ']' after array size expression.");
            if (error == NULL)
            {
                DEBUG_PRINT("parse_fullType: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parse_fullType: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic state
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the close bracket token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parse_fullType: No tokens available after close bracket.\n");
            return NULL;
        }
    }

    AstNode *fullTypeNode = astNode_create(parser->astArena, AST_FULL_TYPE, NULL, children);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parse_fullType: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return fullTypeNode;
}

bool parser_isLiteral(Parser *parser)
{
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isLiteral: No tokens available to check literal.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    switch (currentTokenType)
    {
    case TOKEN_LITERAL_INTEGER:
    case TOKEN_LITERAL_BINARY:
    case TOKEN_LITERAL_OCTAL:
    case TOKEN_LITERAL_HEXADECIMAL:
    case TOKEN_LITERAL_FLOATINGPOINT:
    case TOKEN_LITERAL_CHARACTER:
    case TOKEN_LITERAL_STRING:
    case TOKEN_LITERAL_BOOLEAN:
    case TOKEN_LITERAL_NULL:
        return true;
    default:
        return false; 
    }
    UNREACHABLE();
}

AstNode *parser_parseLiteral(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: No tokens available to parse literal.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_LITERAL_INTEGER &&
        currentTokenType != TOKEN_LITERAL_BINARY &&
        currentTokenType != TOKEN_LITERAL_OCTAL &&
        currentTokenType != TOKEN_LITERAL_HEXADECIMAL &&
        currentTokenType != TOKEN_LITERAL_FLOATINGPOINT &&
        currentTokenType != TOKEN_LITERAL_CHARACTER &&
        currentTokenType != TOKEN_LITERAL_STRING &&
        currentTokenType != TOKEN_LITERAL_BOOLEAN &&
        currentTokenType != TOKEN_LITERAL_NULL)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a literal.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLiteral: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLiteral: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }

    LinkedList *tokens = NULL;

    Token *literalToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (literalToken == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, literalToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the literal token

    AstNode *literalNode = astNode_create(parser->astArena, AST_LITERAL, tokens, NULL);
    if (literalNode == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return literalNode;
}

AstNode *parser_parseProgram(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: No tokens available to parse the program.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    while (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_IMPORT)
    {
        AstNode *import = parser_parseImport(parser); // Sets parser->tokens to the next token after the import statement
        if (import == NULL)
        {
            if (parser->panic) goto parser_parseProgram_Import_Label;
            DEBUG_PRINT("parser_parseProgram: Failed to parse import.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, import);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        parser_parseProgram_Import_Label:
        if(parser->panic) parser_recoverPanic(parser);
        if (parser->panic) return NULL; // If panic state is true, return NULL
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: No tokens available to parse the program.\n");
            return NULL;
        }
    }

    while (((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        LinkedList *currentTokenNode = parser->tokens;
        if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_EXPORT)
        {
            currentTokenNode = currentTokenNode->next; // Look past the export keyword as other statements will handle it
        }

        if (currentTokenNode == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: No tokens available after export keyword.\n");
            return NULL;
        }
        
        My_TokenType currentTokenType = ((Token *)currentTokenNode->data)->type;
        if (currentTokenType == TOKEN_OPEN_PARENTHESIS)
        {
            AstNode *function = parser_parseFunctionDefinition(parser);
            if (function == NULL)
            {
                if (parser->panic) goto parser_parseProgram_Body_Label;
                DEBUG_PRINT("parser_parseProgram: Failed to parse function.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, function);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (currentTokenType == TOKEN_KEYWORD_STRUCT)
        {
            AstNode *structDeclaration = parser_parseStructDeclaration(parser);
            if (structDeclaration == NULL)
            {
                if (parser->panic) goto parser_parseProgram_Body_Label;
                DEBUG_PRINT("parser_parseProgram: Failed to parse struct declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, structDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (currentTokenType == TOKEN_KEYWORD_UNION)
        {
            AstNode *unionDeclaration = parser_parseUnionDeclaration(parser);
            if (unionDeclaration == NULL)
            {
                if (parser->panic) goto parser_parseProgram_Body_Label;
                DEBUG_PRINT("parser_parseProgram: Failed to parse union declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, unionDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (currentTokenType == TOKEN_KEYWORD_ENUM)
        {
            AstNode *enumDeclaration = parser_parseEnumDeclaration(parser);
            if (enumDeclaration == NULL)
            {
                if (parser->panic) goto parser_parseProgram_Body_Label;
                DEBUG_PRINT("parser_parseProgram: Failed to parse enum declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, enumDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (parser_isFullType(parser))
        {
            AstNode *globalDeclaration = parser_parseGlobalVariableDeclaration(parser);
            if (globalDeclaration == NULL)
            {
                if (parser->panic) goto parser_parseProgram_Body_Label;
                DEBUG_PRINT("parser_parseProgram: Failed to parse global declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, globalDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)currentTokenNode->data)->location, "Unexpected token in program.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: error_create failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;
            parser->panic = true; // Set panic state to true
        }

        parser_parseProgram_Body_Label:
        if(parser->panic) parser_recoverPanic(parser);
        if (parser->panic) return NULL; // If panic state is true, return NULL
        else currentTokenNode = parser->tokens;
        if (currentTokenNode == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: No tokens available after processing current token.\n");
            return NULL;
        }
    }

    if (parser->tokens == NULL || ((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        Error *error;
        if (parser->tokens == NULL)
        {
            error = error_create(parser->utilsArena, ERROR_FATAL, (SourceLocation){0}, "End of file not found in the program.");
        }
        else
        {
            error = error_create(parser->utilsArena, ERROR_FATAL, ((Token *)parser->tokens->data)->location, "End of file not found in the program.");
        }
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        return NULL;
    }

    AstNode *program = astNode_create(parser->astArena, AST_PROGRAM, NULL, children);
    if (program == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return program;
}

AstNode *parser_parseImport(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available to parse.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_IMPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'import' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;
    
    parser->tokens = parser->tokens->next; // Move past the import token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available after import keyword.\n");
        return NULL;
    }

    bool isFrom = false;
    if (((Token *)parser->tokens->data)->type == TOKEN_LITERAL_STRING)
    {
        Token *stringLiteralToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (stringLiteralToken == NULL)
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, stringLiteralToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the string literal token
    }
    else if (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
    {
        isFrom = true; // Indicates that this is an import from statement

        AstNode *identifierListNode = parser_parseIdentifierList(parser);
        if (identifierListNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseImport: Panic state is true, skipping import parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseImport: Failed to parse identifier list.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, identifierListNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseImport: No tokens available after import identifiers.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_FROM)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'from' keyword after import identifiers.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic state to true
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the 'from' keyword token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseImport: No tokens available after 'from' keyword.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_LITERAL_STRING)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected string literal after 'from' keyword.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic state to true
            return NULL;
        }

        Token *stringLiteralToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (stringLiteralToken == NULL)
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, stringLiteralToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the string literal token
    }
    else
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected string literal or identifier after import keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available after import statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected semicolon after import statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstType importType = isFrom ? AST_IMPORT_FROM : AST_IMPORT;
    AstNode *importNode = astNode_create(parser->astArena, importType, tokens, children);
    if (importNode == NULL)
    {
        DEBUG_PRINT("parser_parseImport: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return importNode;
}

AstNode *parser_parseIdentifierList(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: No tokens available to parse.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier in identifier list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: No tokens available after comma.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after comma in identifier list.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseIdentifierList: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseIdentifierList: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to skip further parsing
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: No tokens available after identifier.\n");
            return NULL;
        }
    }

    AstNode *identifierListNode = astNode_create(parser->astArena, AST_IDENTIFIER_LIST, tokens, NULL);
    if (identifierListNode == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return identifierListNode;
}

AstNode *parser_parseFunctionDefinition(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available to parse function definition.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_OPEN_PARENTHESIS && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'export' keyword or open parenthesis for function definition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens= NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected open parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *functionReturnParameterListNode = parser_parseReturnParameterList(parser);
    if (functionReturnParameterListNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: Panic state is true, skipping function definition parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseFunctionDefinition: Failed to parse return parameter list.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, functionReturnParameterListNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after return parameter list.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected close parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after close parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected function name after close parenthesis.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *functionNameToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (functionNameToken == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, functionNameToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the function name token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after function name.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected open parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after open parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        AstNode *functionParameterListNode = parser_parseFunctionParameterList(parser);
        if (functionParameterListNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseFunctionDefinition: Panic state is true, skipping function definition parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseFunctionDefinition: Failed to parse function parameter list.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, functionParameterListNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after function parameter list.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected close parenthesis after function parameter list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *functionBodyNode = parser_parseCompoundStatement(parser);
    if (functionBodyNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: Panic state is true, skipping function definition parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseFunctionDefinition: Failed to parse function body.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, functionBodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *functionDefinitionNode = astNode_create(parser->astArena, AST_FUNCTION_DEFINITION, tokens, children);
    if (functionDefinitionNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionDefinitionNode;
}

AstNode *parser_parseReturnParameterList(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: No tokens available to parse return parameter list.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a type or type specifier in return parameter list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: Panic state is true, skipping return parameter list parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseReturnParameterList: Failed to parse return parameter.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: No tokens available after return parameter.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: No tokens available after comma.\n");
            return NULL;
        }

        if (!parser_isFullType(parser))
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a full type after comma in return parameter list.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseReturnParameterList: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic state to true
            return NULL;
        }

        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseReturnParameterList: Panic state is true, skipping return parameter list parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseReturnParameterList: Failed to parse return parameter.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: No tokens available to parse return parameter list.\n");
            return NULL;
        }
    }

    AstNode *returnParameterListNode = astNode_create(parser->astArena, AST_RETURN_PARAMETER_LIST, NULL, children);
    if (returnParameterListNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return returnParameterListNode;
}

AstNode *parser_parseFunctionParameterList(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available to parse function parameter list.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a full type in function parameter list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *functionParameterNode = parser_parseFunctionParameter(parser);
    if (functionParameterNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: Panic state is true, skipping function parameter list parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseFunctionParameterList: Failed to parse first function parameter.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, functionParameterNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available after first function parameter.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available after comma.\n");
            return NULL;
        }

        if (!parser_isFullType(parser))
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a full type after comma in function parameter list.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionParameterList: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic state to true
            return NULL;
        }

        functionParameterNode = parser_parseFunctionParameter(parser);
        if (functionParameterNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseFunctionParameterList: Panic state is true, skipping function parameter list parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseFunctionParameterList: Failed to parse function parameter.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, functionParameterNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available to parse function parameter list.\n");
            return NULL;
        }
    }

    AstNode *functionParameterListNode = astNode_create(parser->astArena, AST_FUNCTION_PARAMETER_LIST, NULL, children);
    if (functionParameterListNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionParameterListNode;
}

AstNode *parser_parseFunctionParameter(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: No tokens available to parse function parameter.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a full type for function parameter.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: Panic state is true, skipping function parameter parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseFunctionParameter: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in function parameter.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;
    parser->tokens = parser->tokens->next; // Move past the identifier token

    AstNode *functionParameterNode = astNode_create(parser->astArena, AST_FUNCTION_PARAMETER, tokens, children);
    if (functionParameterNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionParameterNode;
}

AstNode *parser_parseGlobalVariableDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available to parse variable global declaration.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (!parser_isFullType(parser) && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a full type for global variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }
    
    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, NULL, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Panic state is true, skipping global variable declaration parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in global variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after comma.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_EXPORT)
        {
            Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (exportToken == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Token_create(parser->astArena, tokens, exportToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the export token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after export keyword.\n");
                return NULL;
            }
        }

        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Panic state is true, skipping global variable declaration parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse full type after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available to parse global variable declaration.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in global variable declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true;
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after additional identifier.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
    {
        parser->tokens = parser->tokens->next; // Move past the equals token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after equals sign.\n");
            return NULL;
        }

        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Panic state is true, skipping global variable declaration parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse expression after equals sign.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected semicolon after global variable identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *globalVariableDeclarationNode = astNode_create(parser->astArena, AST_GLOBAL_VARIABLE_DECLARATION, tokens, children);
    if (globalVariableDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return globalVariableDeclarationNode;
}

AstNode *parser_parseStructDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available to parse.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_STRUCT && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'struct' or 'export' keyword for struct declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    parser->tokens = parser->tokens->next; // Move past the struct token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after struct keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' after struct identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *members = parser_parseStructUnionMemberDeclaration(parser);
    if (members == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: Panic state is true, skipping struct declaration parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseStructDeclaration: Failed to parse struct members declaration.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, members);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct members declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '}' to close struct declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *structNode = astNode_create(parser->astArena, AST_STRUCT_DECLARATION, tokens, children);
    if (structNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structNode;
}

AstNode *parser_parseUnionDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available to parse.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_UNION && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'union' or 'export' keyword for union declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    parser->tokens = parser->tokens->next; // Move past the union token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after union keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' after union identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *members = parser_parseStructUnionMemberDeclaration(parser);
    if (members == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: Panic state is true, skipping union declaration.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseUnionDeclaration: Failed to parse union member declaration.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, members);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union member declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '}' to close union declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *unionNode = astNode_create(parser->astArena, AST_UNION_DECLARATION, tokens, children);
    if (unionNode == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return unionNode;
}

AstNode *parser_parseStructUnionMemberDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available to parse struct/union member declaration.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a full type for struct/union member declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in struct/union member declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected semicolon after struct/union member identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after semicolon.\n");
        return NULL;
    }

    while (parser_isFullType(parser))
    {
        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse full type.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after type.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in struct/union member declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to skip further parsing
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after identifier.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected semicolon after struct/union member identifier.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to skip further parsing
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the semicolon token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after semicolon.\n");
            return NULL;
        }
    }

    AstNode *structUnionMemberDeclarationNode = astNode_create(parser->astArena, AST_STRUCT_UNION_MEMBER_DECLARATION, tokens, children);
    if (structUnionMemberDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structUnionMemberDeclarationNode;
}

AstNode *parser_parseStructUnionDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDeclarator: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDeclarator: No tokens available to parse struct/union declarator.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' to start struct/union declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDeclarator: No tokens available after open curly brace.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_DOT)
    {
        AstNode *directDeclaratorNode = parser_parseStructUnionDirectDeclarator(parser);
        if (directDeclaratorNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: Failed to parse struct/union direct declarator.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, directDeclaratorNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *indirectDeclaratorNode = parser_parseStructUnionIndirectDeclarator(parser);
        if (indirectDeclaratorNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: Failed to parse struct/union indirect declarator.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, indirectDeclaratorNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '}' to close struct/union declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *structUniondeclarator = astNode_create(parser->astArena, AST_STRUCT_UNION_DECLARATOR, NULL, children);
    if (structUniondeclarator == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDeclarator: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structUniondeclarator;
}

AstNode *parser_parseStructUnionIndirectDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available to parse struct/union indirect declarator.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *expressionNode = parser_parseExpression(parser);
    if (expressionNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: Failed to parse expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available after expression.\n");
        return NULL;
    }
    
    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available after comma.\n");
            return NULL;
        }

        expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: Failed to parse expression after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available after expression.\n");
            return NULL;
        }
    }

    AstNode *indirectDeclaratorNode = astNode_create(parser->astArena, AST_STRUCT_UNION_INDIRECT_DECLARATOR, NULL, children);
    if (indirectDeclaratorNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return indirectDeclaratorNode;
}

AstNode *parser_parseStructUnionDirectDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available to parse struct/union direct declarator.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_DOT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '.' to start struct/union direct declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the dot token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after dot.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after '.' in struct/union direct declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_EQUALS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '=' after identifier in struct/union direct declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the equals token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after equals.\n");
        return NULL;
    }

    AstNode *expressionNode = parser_parseExpression(parser);
    if (expressionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Panic state is true, skipping struct union direct declarator parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Failed to parse expression after '='.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, expressionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after expression.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after comma.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_DOT)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '.' after comma in struct/union direct declarator.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to true
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the dot token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after dot.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after '.' in struct/union direct declarator.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to true
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after identifier.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_EQUALS)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '=' after identifier in struct/union direct declarator.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to true
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the equals token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after equals.\n");
            return NULL;
        }

        expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Panic state is true, skipping struct union direct declarator parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Failed to parse expression after '='.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after expression.\n");
            return NULL;
        }
    }

    AstNode *structUnionDirectDeclaratorNode = astNode_create(parser->astArena, AST_STRUCT_UNION_DIRECT_DECLARATOR, tokens, children);
    if (structUnionDirectDeclaratorNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structUnionDirectDeclaratorNode; 
}

AstNode *parser_parseEnumDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available to parse enum declaration.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_ENUM && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'enum' keyword to start enum declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    parser->tokens = parser->tokens->next; // Move past the enum keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after enum keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after 'enum' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' to start enum body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *enumValueDeclarationNode = parser_parseEnumValueDeclaration(parser);
    if (enumValueDeclarationNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: Panic state is true, skipping enum declaration parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseEnumDeclaration: Failed to parse enum value declaration.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, enumValueDeclarationNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after enum value declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '}' to close enum body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *enumDeclarationNode = astNode_create(parser->astArena, AST_ENUM_DECLARATION, tokens, children);
    if (enumDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return enumDeclarationNode;
}

AstNode *parser_parseEnumValueDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available to parse enum value declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier for enum value.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *enumValueNode = parser_parseEnumValue(parser);
    if (enumValueNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: Panic state is true, skipping enum value declaration parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseEnumValueDeclaration: Failed to parse enum value.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, enumValueNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COMMA)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ',' after enum value declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the comma token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after comma.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
    {
        enumValueNode = parser_parseEnumValue(parser);
        if (enumValueNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: Panic state is true, skipping enum value declaration parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseEnumValueDeclaration: Failed to parse enum value.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, enumValueNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (((Token *)parser->tokens->data)->type != TOKEN_COMMA)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ',' after enum value declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to true
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after comma.\n");
            return NULL;
        }
    }

    AstNode *enumValueDeclarationNode = astNode_create(parser->astArena, AST_ENUM_VALUE_DECLARATION, NULL, children);
    if (enumValueDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return enumValueDeclarationNode;
}

AstNode *parser_parseEnumValue(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValue: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValue: No tokens available to parse enum value.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier for enum value.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValue: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValue: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValue: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValue: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValue: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
    {
        parser->tokens = parser->tokens->next; // Move past the equals token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValue: No tokens available after equals.\n");
            return NULL;
        }

        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseEnumValue: Panic state is true, skipping enum value parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseEnumValue: Failed to parse expression after '='.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValue: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValue: No tokens available after expression.\n");
            return NULL;
        }
    }

    AstNode *enumValueNode = astNode_create(parser->astArena, AST_ENUM_VALUE, tokens, children);
    if (enumValueNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValue: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return enumValueNode;
}

AstNode *parser_parseStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStatement: No tokens available to parse statement.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_KEYWORD_IF ||
        currentTokenType == TOKEN_KEYWORD_SWITCH )
    {
        AstNode *branchStatementNode = parser_parseBranchStatement(parser);
        if (branchStatementNode == NULL)
        {
            if (parser->panic) goto parser_parseStatement_Label;
            DEBUG_PRINT("parser_parseStatement: Failed to parse branch statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, branchStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (   currentTokenType == TOKEN_KEYWORD_FOR ||
                currentTokenType == TOKEN_KEYWORD_FOREACH ||
                currentTokenType == TOKEN_KEYWORD_WHILE ||
                currentTokenType == TOKEN_KEYWORD_DO )
    {
        AstNode *loopStatementNode = parser_parseLoopStatement(parser);
        if (loopStatementNode == NULL)
        {
            if (parser->panic) goto parser_parseStatement_Label;
            DEBUG_PRINT("parser_parseStatement: Failed to parse loop statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, loopStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_OPEN_CURLY)
    {
        AstNode *compoundStatementNode = parser_parseCompoundStatement(parser);
        if (compoundStatementNode == NULL)
        {
            if (parser->panic) goto parser_parseStatement_Label;
            DEBUG_PRINT("parser_parseStatement: Failed to parse compound statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, compoundStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (   currentTokenType == TOKEN_KEYWORD_GOTO ||
                currentTokenType == TOKEN_KEYWORD_RETURN ||
                currentTokenType == TOKEN_KEYWORD_BREAK ||
                currentTokenType == TOKEN_KEYWORD_CONTINUE)
    {
        AstNode *jumpStatementNode = parser_parseJumpStatement(parser);
        if (jumpStatementNode == NULL)
        {
            if (parser->panic) goto parser_parseStatement_Label;
            DEBUG_PRINT("parser_parseStatement: Failed to parse jump statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, jumpStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *expressionStatementNode = parser_parseExpressionStatement(parser);
        if (expressionStatementNode == NULL)
        {
            if (parser->panic) goto parser_parseStatement_Label;
            DEBUG_PRINT("parser_parseStatement: Failed to parse expression statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    parser_parseStatement_Label:
    if (parser->panic) parser_recoverPanic(parser);
    if (parser->panic) return NULL; // If panic state is true, return NULL
    AstNode *statementNode = astNode_create(parser->astArena, AST_STATEMENT, NULL, children);
    if (statementNode == NULL)
    {
        DEBUG_PRINT("parser_parseStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return statementNode;
}

AstNode *parser_parseBranchStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseBranchStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBranchStatement: No tokens available to parse branch statement.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_IF &&
        currentTokenType != TOKEN_KEYWORD_SWITCH)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'if' or 'switch' keyword to start branch statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_IF)
    {
        AstNode *ifStatement = parser_parseIfStatement(parser);
        if (ifStatement == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseBranchStatement: Panic state is true, skipping branch statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseBranchStatement: Failed to parse if statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, ifStatement);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *switchStatement = parser_parseSwitchStatement(parser);
        if (switchStatement == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseBranchStatement: Panic state is true, skipping branch statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseBranchStatement: Failed to parse switch condition.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, switchStatement);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *branchStatementNode = astNode_create(parser->astArena, AST_BRANCH_STATEMENT, NULL, children);
    if (branchStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseBranchStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return branchStatementNode;
}

AstNode *parser_parseIfStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available to parse if statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_IF)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'if' keyword to start if statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'if' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after 'if' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' after 'if' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseIfStatement: Panic state is true, skipping if statement parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseIfStatement: Failed to parse condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close condition expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *ifBodyNode = parser_parseStatement(parser);
    if (ifBodyNode == NULL)
    {
        // Statement can't panic, so we don't check parser->panic here
        DEBUG_PRINT("parser_parseIfStatement: Failed to parse if body statement.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, ifBodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after if body statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_ELSE)
    {
        parser->tokens = parser->tokens->next; // Move past the 'else' keyword
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: No tokens available after 'else' keyword.\n");
            return NULL;
        }

        AstNode *elseBodyNode = parser_parseStatement(parser);
        if (elseBodyNode == NULL)
        {
            // Statement can't panic, so we don't check parser->panic here
            DEBUG_PRINT("parser_parseIfStatement: Failed to parse else body statement.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, elseBodyNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: No tokens available after else body statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_ENDIF)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'endif' keyword to end if statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'endif' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after 'endif' keyword.\n");
        return NULL;
    }

    AstNode *ifStatementNode = astNode_create(parser->astArena, AST_IF_STATEMENT, NULL, children);
    if (ifStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return ifStatementNode;
}

AstNode *parser_parseSwitchStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available to parse switch statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_SWITCH)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'switch' keyword to start switch statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'switch' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after 'switch' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' after 'switch' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: Panic state is true, skipping switch statement parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseSwitchStatement: Failed to parse switch condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after switch condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close switch condition expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' to start switch body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after open curly brace.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_CASE ||
           ((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_DEFAULT)
    {
        AstNode *caseNode;
        if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_CASE)
        {
            caseNode = parser_parseSwitchCase(parser);
        }
        else
        {
            caseNode = parser_parseSwitchDefault(parser);
        }
        if (caseNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseSwitchStatement: Panic state is true, skipping switch case parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseSwitchStatement: Failed to parse case statement.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, caseNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after case statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '}' to close switch body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *switchNode = astNode_create(parser->astArena, AST_SWITCH_STATEMENT, NULL, children);
    if (switchNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return switchNode;
}

AstNode *parser_parseSwitchCase(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available to parse case statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_CASE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'case' keyword to start case statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'case' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available after 'case' keyword.\n");
        return NULL;
    }

    AstNode *caseValueNode = parser_parseExpression(parser);
    if (caseValueNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseSwitchCase: Panic state is true, skipping switch case expression.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseSwitchCase: Failed to parse case value expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, caseValueNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available after case value expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ':' after case value expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available after colon.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_CASE &&
        ((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_DEFAULT)
    {
        AstNode *caseBodyNode = parser_parseStatement(parser);
        if (caseBodyNode == NULL)
        {
            // Statement can't panic, so we don't check parser->panic here
            DEBUG_PRINT("parser_parseSwitchCase: Failed to parse case body statement.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, caseBodyNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *caseNode = astNode_create(parser->astArena, AST_SWITCH_CASE, NULL, children);
    if (caseNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return caseNode;
}

AstNode *parser_parseSwitchDefault(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: No tokens available to parse default statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_DEFAULT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'default' keyword to start default statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'default' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: No tokens available after 'default' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ':' after 'default' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: No tokens available after colon.\n");
        return NULL;
    }

    AstNode *defaultBodyNode = parser_parseStatement(parser);
    if (defaultBodyNode == NULL)
    {
        // Statement can't panic, so we don't check parser->panic here
        DEBUG_PRINT("parser_parseSwitchDefault: Failed to parse default body statement.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, defaultBodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *defaultNode = astNode_create(parser->astArena, AST_SWITCH_DEFAULT, NULL, children);
    if (defaultNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return defaultNode;
}

AstNode *parser_parseLoopStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseLoopStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLoopStatement: No tokens available to parse loop statement.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_FOR &&
        currentTokenType != TOKEN_KEYWORD_FOREACH &&
        currentTokenType != TOKEN_KEYWORD_WHILE &&
        currentTokenType != TOKEN_KEYWORD_DO)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'for', 'foreach', 'while', or 'do' keyword to start loop statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_FOR)
    {
        AstNode *forStatementNode = parser_parseForStatement(parser);
        if (forStatementNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseLoopStatement: Panic state is true, skipping parsing loop statement.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse for statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, forStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_FOREACH)
    {
        AstNode *foreachStatementNode = parser_parseForeachStatement(parser);
        if (foreachStatementNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseLoopStatement: Panic state is true, skipping parsing loop statement.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse foreach statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, foreachStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_WHILE)
    {
        AstNode *whileStatementNode = parser_parseWhileStatement(parser);
        if (whileStatementNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseLoopStatement: Panic state is true, skipping parsing loop statement.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse while statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, whileStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else // DO_WHILE
    {
        AstNode *doWhileStatementNode = parser_parseDoWhileStatement(parser);
        if (doWhileStatementNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseLoopStatement: Panic state is true, skipping parsing loop statement.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse do-while statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, doWhileStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *loopStatementNode = astNode_create(parser->astArena, AST_LOOP_STATEMENT, NULL, children);
    if (loopStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseLoopStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return loopStatementNode;
}

AstNode *parser_parseForStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available to parse for statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_FOR)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'for' keyword to start for statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'for' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after 'for' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' after 'for' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        AstNode *initNode = parser_parseForInitializer(parser);
        if (initNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseForStatement: Panic mode is enabled, skipping to next statement.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseForStatement: Failed to parse for initializer.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, initNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: No tokens available after first part of for statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' after first part of for statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the first semicolon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after first part of for statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        AstNode *conditionNode = parser_parseForCondition(parser);
        if (conditionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseForStatement: Panic state is true, skipping for statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseForStatement: Failed to parse condition expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: No tokens available after condition expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' after condition expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the second semicolon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after second semicolon.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        AstNode *incrementNode = parser_parseForIncrementation(parser);
        if (incrementNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseForStatement: Panic state is true, skipping for statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseForStatement: Failed to parse increment expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, incrementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: No tokens available after increment expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close for statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *bodyNode = parser_parseStatement(parser);
    if (bodyNode == NULL)
    {
        // Statement can't panic, so we don't check parser->panic here
        DEBUG_PRINT("parser_parseForStatement: Failed to parse for statement body.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, bodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *forStatementNode = astNode_create(parser->astArena, AST_FOR_STATEMENT, NULL, children);
    if (forStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return forStatementNode;
}

AstNode *parser_parseForInitializer(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: No tokens available to parse for initializer.\n");
        return NULL;
    }

    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: Reached end of tokens while parsing for initializer.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    if (parser_isFullType(parser))
    {
        bool success = false;
        AstNode *variableDeclarationNode = parser_tryParseVariableDeclaration(parser, &success);
        if (!success)
        {
            parser->panic = false; // Reset panic mode
            goto parser_parseForInitializer_Assignment_Label;
        }
        if (variableDeclarationNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseForInitializer: Panic state is true, skipping for initializer parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseForInitializer: Failed to parse variable declaration.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, variableDeclarationNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForInitializer: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        parser_parseForInitializer_Assignment_Label:
        ;
        AstNode *assignementExpretionNode = parser_parseAssignmentExpression(parser);
        if (assignementExpretionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseForInitializer: Panic state is true, skipping for initializer parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseForInitializer: Failed to parse expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, assignementExpretionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForInitializer: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *initializerNode = astNode_create(parser->astArena, AST_FOR_INITIALIZER, NULL, children);
    if (initializerNode == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return initializerNode;
}

AstNode *parser_parseForCondition(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: No tokens available to parse for condition.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseForCondition: Panic state is true, skipping condition parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseForCondition: Failed to parse condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *conditionAstNode = astNode_create(parser->astArena, AST_FOR_CONDITION, NULL, children);
    if (conditionAstNode == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return conditionAstNode;
}

AstNode *parser_parseForIncrementation(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: No tokens available to parse for incrementation.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *incrementNode = parser_parseExpression(parser);
    if (incrementNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseForIncrementation: Panic state is true, skipping incrementation parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseForIncrementation: Failed to parse increment expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, incrementNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *incrementationAstNode = astNode_create(parser->astArena, AST_FOR_INCREMENTATION, NULL, children);
    if (incrementationAstNode == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return incrementationAstNode;
}

AstNode *parser_parseForeachStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available to parse foreach statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_FOREACH)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'foreach' keyword to start foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'foreach' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after 'foreach' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' after 'foreach' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

   AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseForeachStatement: Panic state is true, skipping foreach statement parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseForeachStatement: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected an identifier after type in foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ':' after identifier in foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after colon.\n");
        return NULL;
    }

    identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the second identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after second identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *bodyStatementNode = parser_parseStatement(parser);
    if (bodyStatementNode == NULL)
    {
        // Statements can't panic, so we don't check for panic state here
        DEBUG_PRINT("parser_parseForeachStatement: Failed to parse foreach statement body.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, bodyStatementNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *foreachStatementNode = astNode_create(parser->astArena, AST_FOREACH_STATEMENT, tokens, children);
    if (foreachStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return foreachStatementNode;
}

AstNode *parser_parseWhileStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available to parse while statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_WHILE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'while' keyword to start while statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'while' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after 'while' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' after 'while' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseWhileStatement: Panic state is true, skipping while statement parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseWhileStatement: Failed to parse condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close while statement condition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *bodyNode = parser_parseStatement(parser);
    if (bodyNode == NULL)
    {
        // Statements can't panic, so we don't check for panic mode here
        DEBUG_PRINT("parser_parseWhileStatement: Failed to parse while statement body.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, bodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *whileStatementNode = astNode_create(parser->astArena, AST_WHILE_STATEMENT, NULL, children);
    if (whileStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return whileStatementNode;
}

AstNode *parser_parseDoWhileStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available to parse do-while statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_DO)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'do' keyword to start do-while statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'do' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after 'do' keyword.\n");
        return NULL;
    }

    AstNode *bodyNode = parser_parseStatement(parser);
    if (bodyNode == NULL)
    {
        // Statements can't panic, so we don't check for panic mode here
        DEBUG_PRINT("parser_parseDoWhileStatement: Failed to parse do-while statement body.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, bodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after do-while body.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_WHILE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'while' keyword after do-while body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'while' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after 'while' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' after 'while' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: Panic state is true, skipping do while statement parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseDoWhileStatement: Failed to parse condition expression.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close do-while statement condition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' after do-while condition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *doWhileStatementNode = astNode_create(parser->astArena, AST_DO_WHILE_STATEMENT, NULL, children);
    if (doWhileStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return doWhileStatementNode;
}

AstNode *parser_parseCompoundStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: No tokens available to parse compound statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' to start compound statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: No tokens available after open curly brace.\n");
        return NULL;
    }

    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: No next token available after open curly brace.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        if (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER && ((Token *)parser->tokens->next->data)->type == TOKEN_COLON)
        {
            AstNode *labelNode = parser_parseLabel(parser);
            if (labelNode == NULL)
            {
                if (parser->panic)
                {
                    DEBUG_PRINT("parser_parseCompoundStatement: Panic state is true, skipping compound statement parsing.\n");
                    return NULL;
                }
                DEBUG_PRINT("parser_parseCompoundStatement: Failed to parse label.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, labelNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else
        {
            AstNode *statementNode = parser_parseStatement(parser);
            if (statementNode == NULL)
            {
                // Statements can't panic, so we don't check for panic mode here
                DEBUG_PRINT("parser_parseCompoundStatement: Failed to parse statement.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, statementNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: No tokens available while parsing compound statement.\n");
            return NULL;
        }

        if (parser->tokens->next == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: Reached end of tokens while parsing compound statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '}' to close compound statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '}' to close compound statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *compoundStatementNode = astNode_create(parser->astArena, AST_COMPOUND_STATEMENT, NULL, children);
    if (compoundStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return compoundStatementNode;
}

AstNode *parser_parseLabel(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: No tokens available to parse label.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier to start label.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *tokens = NULL;

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->utilsArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ':' after label identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token

    AstNode *labelNode = astNode_create(parser->astArena, AST_LABEL, tokens, NULL);
    if (labelNode == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return labelNode;
}

AstNode *parser_parseExpressionStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: No tokens available to parse expression statement.\n");
        return NULL;
    }

    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: No next token available after current token.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    if (((Token *)parser->tokens->data)->type == TOKEN_SEMICOLON);
    else if (parser_isFullType(parser))
    {
        bool success = false;
        AstNode *variableDeclarationNode = parser_tryParseVariableDeclaration(parser, &success);
        if (!success)
        {
            parser->panic = false; // Reset panic mode
            goto parser_parseExpressionStatement_Expression_Label;
        }
        if (variableDeclarationNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseExpressionStatement: Panic state is true, skipping expression statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseExpressionStatement: Failed to parse variable declaration.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, variableDeclarationNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: No tokens available after variable declaration.\n");
            return NULL;
        }
    }
    else
    {
        parser_parseExpressionStatement_Expression_Label:
        ;
        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseExpressionStatement: Panic state is true, skipping expression statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseExpressionStatement: Failed to parse expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: No tokens available after expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' after expression statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *expressionStatementNode = astNode_create(parser->astArena, AST_EXPRESSION_STATEMENT, NULL, children);
    if (expressionStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return expressionStatementNode;
}

AstNode *parser_parseVariableDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available to parse variable declaration.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected full type to start variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: Panic mode enabled, returning NULL.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after comma.\n");
            return NULL;
        }

        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: Panic mode enabled, returning NULL.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse full type after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after type.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after comma in variable declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to true
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after identifier.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
    {
        parser->tokens = parser->tokens->next; // Move past the assignment token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after assignment.\n");
            return NULL;
        }

        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: Panic mode enabled, returning NULL.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse assignment expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *variableDeclarationNode = astNode_create(parser->astArena, AST_VARIABLE_DECLARATION, tokens, children);
    if (variableDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return variableDeclarationNode;
}

AstNode *parser_tryParseVariableDeclaration(Parser *parser, bool *success)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_tryParseVariableDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_tryParseVariableDeclaration: No tokens available to parse variable declaration.\n");
        return NULL;
    }

    LinkedList *start = parser->tokens;
    *success = true;

    if (!parser_isFullType(parser))
    {
        parser->tokens = start;
        parser->panic = true;
        *success = false;
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: Panic mode enabled, returning NULL.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        parser->tokens = start;
        parser->panic = true;
        *success = false;
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after comma.\n");
            return NULL;
        }

        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: Panic mode enabled, returning NULL.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse full type after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after type.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after comma in variable declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to true
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after identifier.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
    {
        parser->tokens = parser->tokens->next; // Move past the assignment token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after assignment.\n");
            return NULL;
        }

        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: Panic mode enabled, returning NULL.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse assignment expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *variableDeclarationNode = astNode_create(parser->astArena, AST_VARIABLE_DECLARATION, tokens, children);
    if (variableDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return variableDeclarationNode;
}

AstNode *parser_parseJumpStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseJumpStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseJumpStatement: No tokens available to parse jump statement.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_GOTO &&
        currentTokenType != TOKEN_KEYWORD_RETURN &&
        currentTokenType != TOKEN_KEYWORD_BREAK &&
        currentTokenType != TOKEN_KEYWORD_CONTINUE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'goto', 'return', 'break', or 'continue' keyword to start jump statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_GOTO)
    {
        AstNode *gotoNode = parser_parseGotoStatement(parser);
        if (gotoNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseJumpStatement: Panic state is true, skipping jump statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse goto statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, gotoNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_RETURN)
    {
        AstNode *returnNode = parser_parseReturnStatement(parser);
        if (returnNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseJumpStatement: Panic state is true, skipping jump statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse return statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, returnNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_BREAK)
    {
        AstNode *breakNode = parser_parseBreakStatement(parser);
        if (breakNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseJumpStatement: Panic state is true, skipping jump statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse break statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, breakNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_CONTINUE)
    {
        AstNode *continueNode = parser_parseContinueStatement(parser);
        if (continueNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseJumpStatement: Panic state is true, skipping jump statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse continue statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, continueNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *jumpStatementNode = astNode_create(parser->astArena, AST_JUMP_STATEMENT, NULL, children);
    if (jumpStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseJumpStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return jumpStatementNode;
}

AstNode *parser_parseGotoStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: No tokens available to parse goto statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_GOTO)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'goto' keyword to start goto statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'goto' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: No tokens available after 'goto' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after 'goto' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_WHEN)
    {
        parser->tokens = parser->tokens->next; // Move past the 'when' keyword token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: No tokens available after 'when' keyword.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' after 'when' keyword in goto statement.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to skip further parsing
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the open parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: No tokens available after open parenthesis.\n");
            return NULL;
        }

        AstNode *conditionNode = parser_parseExpression(parser);
        if (conditionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseGotoStatement: Panic state is true, skipping goto statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseGotoStatement: Failed to parse condition expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, conditionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close condition in goto statement.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true; // Set panic mode to skip further parsing
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the close parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: No tokens available after close parenthesis.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' to end goto statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *gotoStatementNode = astNode_create(parser->astArena, AST_GOTO_STATEMENT, tokens, children);
    if (gotoStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return gotoStatementNode;
}

AstNode *parser_parseReturnStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: No tokens available to parse return statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_RETURN)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'return' keyword to start return statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'return' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: No tokens available after 'return' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseReturnStatement: Panic state is true, skipping return statement parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseReturnStatement: Failed to parse return expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: No tokens available after return expression.\n");
            return NULL;
        }

        while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
        {
            parser->tokens = parser->tokens->next; // Move past the comma token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseReturnStatement: No tokens available after comma.\n");
                return NULL;
            }

            expressionNode = parser_parseExpression(parser);
            if (expressionNode == NULL)
            {
                if (parser->panic)
                {
                    DEBUG_PRINT("parser_parseReturnStatement: Panic state is true, skipping return statement parsing.\n");
                    return NULL;
                }
                DEBUG_PRINT("parser_parseReturnStatement: Failed to parse return expression after comma.\n");
                return NULL;
            }
            head = linkedList_Ast_create(parser->astArena, children, expressionNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseReturnStatement: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;

            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseReturnStatement: No tokens available after return expression.\n");
                return NULL;
            }
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' to end return statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *returnStatementNode = astNode_create(parser->astArena, AST_RETURN_STATEMENT, NULL, children);
    if (returnStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return returnStatementNode;
}

AstNode *parser_parseBreakStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: No tokens available to parse break statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_BREAK)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'break' keyword to start break statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'break' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: No tokens available after 'break' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' to end break statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *breakStatementNode = astNode_create(parser->astArena, AST_BREAK_STATEMENT, NULL, NULL);
    if (breakStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return breakStatementNode;
}

AstNode *parser_parseContinueStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: No tokens available to parse continue statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_CONTINUE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'continue' keyword to start continue statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'continue' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: No tokens available after 'continue' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ';' to end continue statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *continueStatementNode = astNode_create(parser->astArena, AST_CONTINUE_STATEMENT, NULL, NULL);
    if (continueStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return continueStatementNode;
}

AstNode *parser_parseExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: No tokens available to parse expression.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *binaryExpressionNode = parser_parseBinaryExpression(parser, 0);
    if (binaryExpressionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseExpression: Panic state is true, skipping expression parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseExpression: Failed to parse logical or expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, binaryExpressionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;
    
    AstNode *expressionNode = astNode_create(parser->astArena, AST_EXPRESSION, NULL, children);
    if (expressionNode == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return expressionNode;
}

AstNode *parser_parseAssignmentExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpression: No tokens available to parse assignment expression.\n");
        return NULL;
    }

    AstNode *unaryStartNode = parser_parseUnaryExpression(parser);
    if (unaryStartNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseAssignmentExpression: Panic state is true, skipping assignment expression parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseAssignmentExpression: Failed to parse unary expression.\n");
        return NULL;
    }

    AstNode *assignmentNode = parser_parseAssignmentExpressionFromUnary(parser, unaryStartNode);
    if (assignmentNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseAssignmentExpression: Panic state is true, skipping assignment expression parsing from unary.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseAssignmentExpression: Failed to parse assignment expression from unary.\n");
        return NULL;
    }
    return assignmentNode;
}

AstNode *parser_parseAssignmentExpressionFromUnary(Parser *parser, AstNode *unaryStartNode)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: Parser is NULL.\n");
        return NULL;
    }

    if (unaryStartNode == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: Unary start node is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: No tokens available to parse assignment expression.\n");
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    LinkedList *head = linkedList_Ast_create(parser->astArena, children, unaryStartNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token

        AstNode *nextUnaryNode = parser_parseUnaryExpression(parser);
        if (nextUnaryNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: Panic state is true, skipping assignment expression parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: Failed to parse next unary expression.\n");
            return NULL;
        }
        LinkedList *nextHead = linkedList_Ast_create(parser->astArena, children, nextUnaryNode);
        if (nextHead == NULL)
        {
            DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = nextHead;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: No tokens available after unary expression.\n");
            return NULL;
        }
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_EQUALS && currentTokenType != TOKEN_PLUS_EQUALS &&
        currentTokenType != TOKEN_MINUS_EQUALS && currentTokenType != TOKEN_STAR_EQUALS &&
        currentTokenType != TOKEN_SLASH_EQUALS && currentTokenType != TOKEN_PERCENT_EQUALS &&
        currentTokenType != TOKEN_AMPERSAND_EQUALS && currentTokenType != TOKEN_PIPE_EQUALS &&
        currentTokenType != TOKEN_CARET_EQUALS && currentTokenType != TOKEN_DOUBLE_GREATER_THAN_EQUALS &&
        currentTokenType != TOKEN_DOUBLE_LESS_THAN_EQUALS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected assignment operator after unary expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    Token *assignementOperatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (assignementOperatorToken == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, assignementOperatorToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the assignment operator token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: No tokens available after assignment operator.\n");
        return NULL;
    }

    AstNode *rightExpressionNode = parser_parseExpression(parser);
    if (rightExpressionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: Panic state is true, skipping right expression parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: Failed to parse right expression after assignment operator.\n");
        return NULL;
    }
    LinkedList *rightHead = linkedList_Ast_create(parser->astArena, children, rightExpressionNode);
    if (rightHead == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = rightHead;

    AstNode *assignmentNode = astNode_create(parser->astArena, AST_ASSIGNMENT_EXPRESSION, tokens, children);
    if (assignmentNode == NULL)
    {
        DEBUG_PRINT("parser_parseAssignmentExpressionFromUnary: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return assignmentNode;
}

int parser_getPrecedence(My_TokenType type)
{
    switch (type)
    {
    case TOKEN_STAR:
    case TOKEN_SLASH:
    case TOKEN_PERCENT:
        return 12; // Multiplicative precedence
    case TOKEN_PLUS:
    case TOKEN_MINUS:
        return 11; // Additive precedence
    case TOKEN_DOUBLE_GREATER_THAN:
    case TOKEN_DOUBLE_LESS_THAN:
        return 10; // Shift precedence
    case TOKEN_LESS_THAN:
    case TOKEN_GREATER_THAN:
    case TOKEN_LESS_THAN_EQUALS:
    case TOKEN_GREATER_THAN_EQUALS:
        return 9; // Relational precedence
    case TOKEN_DOUBLE_EQUALS:
    case TOKEN_EXCLAMATION_EQUALS:
        return 8; // Equality and inequality precedence
    case TOKEN_AMPERSAND:
        return 7; // Bitwise AND precedence
    case TOKEN_CARET:
        return 6; // Bitwise XOR precedence
    case TOKEN_PIPE:
        return 5; // Bitwise OR precedence
    case TOKEN_DOUBLE_AMPERSAND:
        return 4; // Logical AND precedence
    case TOKEN_DOUBLE_PIPE:
        return 3; // Logical OR precedence
    case TOKEN_EQUALS:
    case TOKEN_PLUS_EQUALS:
    case TOKEN_MINUS_EQUALS:
    case TOKEN_STAR_EQUALS:
    case TOKEN_SLASH_EQUALS:
    case TOKEN_PERCENT_EQUALS:
    case TOKEN_AMPERSAND_EQUALS:
    case TOKEN_PIPE_EQUALS:
    case TOKEN_CARET_EQUALS:
    case TOKEN_DOUBLE_GREATER_THAN_EQUALS:
    case TOKEN_DOUBLE_LESS_THAN_EQUALS:
        return 2; // Assignment precedence
    case TOKEN_COMMA:
        return 1; // Comma precedence
    default:
        return 0; // Default precedence for other operators
    }
    UNREACHABLE();
}

AstType parser_getOperatorType(My_TokenType type)
{
    switch (type)
    {
    case TOKEN_STAR:
    case TOKEN_SLASH:
    case TOKEN_PERCENT:
        return AST_MULTIPLICATIVE_EXPRESSION;
    case TOKEN_PLUS:
    case TOKEN_MINUS:
        return AST_ADDITIVE_EXPRESSION;
    case TOKEN_DOUBLE_GREATER_THAN:
    case TOKEN_DOUBLE_LESS_THAN:
        return AST_SHIFT_EXPRESSION;
    case TOKEN_LESS_THAN:
    case TOKEN_LESS_THAN_EQUALS:
    case TOKEN_GREATER_THAN:
    case TOKEN_GREATER_THAN_EQUALS:
        return AST_RELATIONAL_EXPRESSION;
    case TOKEN_DOUBLE_EQUALS:
    case TOKEN_EXCLAMATION_EQUALS:
        return AST_EQUALITY_EXPRESSION;
    case TOKEN_AMPERSAND:
        return AST_BITWISE_AND_EXPRESSION;
    case TOKEN_CARET:
        return AST_BITWISE_XOR_EXPRESSION;
    case TOKEN_PIPE:
        return AST_BITWISE_OR_EXPRESSION;
    case TOKEN_DOUBLE_AMPERSAND:
        return AST_LOGICAL_AND_EXPRESSION;
    case TOKEN_DOUBLE_PIPE:
        return AST_LOGICAL_OR_EXPRESSION;
    default:
        return 0; // Unknown operator type
    }
}

AstNode *parser_parseBinaryExpression(Parser *parser, int parentPrecedence)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseBinaryExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBinaryExpression: No tokens available to parse binary expression.\n");
        return NULL;
    }

    AstNode *left = parser_parseUnaryExpression(parser);
    if (left == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: Panic state is true, skipping binary expression parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseBinaryExpression: Failed to parse unary expression.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBinaryExpression: No tokens available after unary expression.\n");
        return NULL;
    }

    while (true)
    {
        LinkedList *tokens = NULL;
        LinkedList *children = NULL;

        int precedence = parser_getPrecedence(((Token *)parser->tokens->data)->type);
        AstType operatorType = parser_getOperatorType(((Token *)parser->tokens->data)->type);
        if (precedence == 1 || precedence == 2) // Assignment , or =
        {
            if (parentPrecedence != 0)
            {
                Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Assignment expressions are not allowed in this context.");
                if (error == NULL)
                {
                    DEBUG_PRINT("parser_parseBinaryExpression: error_create failed with errno %d\n", errno);
                    return NULL;
                }
                LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parseBinaryExpression: linkedList_Error_create failed with errno %d\n", errno);
                    return NULL;
                }
                parser->errors = head;

                parser->panic = true; // Set panic mode to true
                return NULL;
            }

            AstNode *assignmentNode = parser_parseAssignmentExpressionFromUnary(parser, left);
            if (assignmentNode == NULL)
            {
                if (parser->panic)
                {
                    DEBUG_PRINT("parser_parseBinaryExpression: Parser is in panic mode, returning NULL.\n");
                    return NULL; // Return NULL if parser is in panic mode
                }
                DEBUG_PRINT("parser_parseBinaryExpression: Failed to parse assignment expression from unary.\n");
                return NULL;
            }
            return assignmentNode;
        }
        else if (precedence == 0 || precedence <= parentPrecedence)
        {
            break;
        }

        LinkedList *head = linkedList_Ast_create(parser->astArena, children, left);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        Token *operatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (operatorToken == NULL)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, operatorToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the operator token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: No tokens available after operator.\n");
            return NULL;
        }

        AstNode *right = parser_parseBinaryExpression(parser, precedence);
        if (right == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseBinaryExpression: Panic state is true, skipping binary expression parsing.\n");
                return NULL; // Return NULL if parser is in panic mode
            }
            DEBUG_PRINT("parser_parseBinaryExpression: Failed to parse right unary expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, right);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: No tokens available after right unary expression.\n");
            return NULL;
        }

        left = astNode_create(parser->astArena, operatorType, tokens, children);
        if (left == NULL)
        {
            DEBUG_PRINT("parser_parseBinaryExpression: astNode_create failed with errno %d\n", errno);
            return NULL;
        }
    }
    return left; // Return the final expression node
}

AstNode *parser_parseUnaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseUnaryExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnaryExpression: No tokens available to parse unary expression.\n");
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_DOUBLE_PLUS || currentTokenType == TOKEN_DOUBLE_MINUS)
    {
        Token *operatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (operatorToken == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, operatorToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the unary operator token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: No tokens available after unary operator.\n");
            return NULL;
        }

        AstNode *unaryExpressionNode = parser_parseUnaryExpression(parser);
        if (unaryExpressionNode == NULL)
        {
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseUnaryExpression: No tokens available after unary operator.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse unary expression after operator.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, unaryExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (   currentTokenType == TOKEN_MINUS || 
                currentTokenType == TOKEN_STAR || currentTokenType == TOKEN_AMPERSAND ||
                currentTokenType == TOKEN_TILDE || currentTokenType == TOKEN_EXCLAMATION)
    {
        Token *operatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (operatorToken == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, operatorToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the unary operator token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: No tokens available after unary operator.\n");
            return NULL;
        }

        AstNode *typeCastExpressionNode = parser_parseTypeCastExpression(parser);
        if (typeCastExpressionNode == NULL)
        {
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseUnaryExpression: No tokens available after unary operator.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse unary expression after operator.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, typeCastExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *typeCastExpressionNode = parser_parseTypeCastExpression(parser);
        if (typeCastExpressionNode == NULL)
        {
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseUnaryExpression: No tokens available after unary expression.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse typecast expression.\n");
            return NULL;
        }
        return typeCastExpressionNode; // Return the type cast expression directly if no unary operator
    }

    AstNode *unaryExpressionNode = astNode_create(parser->astArena, AST_UNARY_EXPRESSION, tokens, children);
    if (unaryExpressionNode == NULL)
    {
        DEBUG_PRINT("parser_parseUnaryExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return unaryExpressionNode;
}

AstNode *parser_parseTypeCastExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available to parse type cast expression.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    LinkedList *lookBack = parser->tokens;
    parser->tokens = parser->tokens->next; // Temporarily move to the next token to check for type cast
    bool isTypeCast = ((Token *)lookBack->data)->type == TOKEN_OPEN_PARENTHESIS && parser_isFullType(parser);
    parser->tokens = lookBack; // Restore the tokens list

    if (!isTypeCast)
    {
        AstNode *postfixExpressionNode = parser_parsePostfixExpression(parser);
        if (postfixExpressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseTypeCastExpression: Panic state is true, skipping postfix expression parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseTypeCastExpression: Failed to parse unary expression.\n");
            return NULL;
        }
        return postfixExpressionNode; // Return the postfix expression directly if not a type cast
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available after full type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close type cast expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *typeCastExpressionNode = parser_parseTypeCastExpression(parser);
    if (typeCastExpressionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: Panic state is true, skipping type cast expression parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseTypeCastExpression: Failed to parse type cast expression after type.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, typeCastExpressionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *typeCastExpression = astNode_create(parser->astArena, AST_TYPE_CAST_EXPRESSION, NULL, children);
    if (typeCastExpression == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return typeCastExpression;
}

AstNode *parser_parsePostfixExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: No tokens available to parse postfix expression.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_OPEN_CURLY && currentTokenType != TOKEN_IDENTIFIER && !parser_isLiteral(parser) && currentTokenType != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier, literal, or '(' to start postfix expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *children = NULL;

    if (((Token *)parser->tokens->data)->type == TOKEN_OPEN_CURLY)
    {
        AstNode *structUnionDeclarator = parser_parseStructUnionDeclarator(parser);
        if (structUnionDeclarator == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parsePostfixExpression: Panic state is true, skipping struct or union declarator parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parsePostfixExpression: Failed to parse struct or union declarator.\n");
            return NULL;
        }
        return structUnionDeclarator; // Return the struct or union declarator directly instead of creating a postfix expression node
    }

    AstNode *primaryExpressionNode = parser_parsePrimaryExpression(parser);
    if (primaryExpressionNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: Panic state is true, skipping primary expression parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parsePostfixExpression: Failed to parse primary expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, primaryExpressionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: No tokens available after primary expression.\n");
        return NULL;
    }

    bool hasPostfixPrime = false;
    while (parser_isPostfixPrimeExpression(parser))
    {
        hasPostfixPrime = true;
        AstNode *postfixPrimeNode = parser_parsePostfixPrimeExpression(parser);
        if (postfixPrimeNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parsePostfixExpression: Panic state is true, skipping postfix prime expression parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parsePostfixExpression: Failed to parse postfix prime expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, postfixPrimeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: No tokens available after postfix prime expression.\n");
            return NULL;
        }
    }

    if (!hasPostfixPrime)
    {
        return primaryExpressionNode; // If no postfix prime expressions, return the primary expression directly
    }

    AstNode *postfixExpressionNode = astNode_create(parser->astArena, AST_POSTFIX_EXPRESSION, NULL, children);
    if (postfixExpressionNode == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return postfixExpressionNode;
}

bool parser_isPostfixPrimeExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_isPostfixPrimeExpression: Parser is NULL.\n");
        return false;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isPostfixPrimeExpression: No tokens available to check for postfix prime expression.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    return (currentTokenType == TOKEN_OPEN_PARENTHESIS || currentTokenType == TOKEN_OPEN_BRACKET || currentTokenType == TOKEN_DOT ||
            currentTokenType == TOKEN_DOUBLE_PLUS || currentTokenType == TOKEN_DOUBLE_MINUS);
}

AstNode *parser_parsePostfixPrimeExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixPrimeExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixPrimeExpression: No tokens available to parse postfix prime expression.\n");
        return NULL;
    }

    if (!parser_isPostfixPrimeExpression(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(', '[', '.', '++', or '--' to start postfix prime expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;    
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_OPEN_PARENTHESIS)
    {
        AstNode *functionCallNode = parser_parseFunctionCallExpression(parser);
        if (functionCallNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: Panic state is true, skipping function call parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: Failed to parse function call.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, functionCallNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_OPEN_BRACKET)
    {
        AstNode *arrayIndexingNode = parser_parseArrayIndexingExpression(parser);
        if (arrayIndexingNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: Panic state is true, skipping array indexing parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: Failed to parse array indexing.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, arrayIndexingNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        if (currentTokenType == TOKEN_DOT)
        {
            parser->tokens = parser->tokens->next; // Move past the dot token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: No tokens available after dot.\n");
                return NULL;
            }

            if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
            {
                Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after '.' in postfix prime expression.");
                if (error == NULL)
                {
                    DEBUG_PRINT("parser_parsePostfixPrimeExpression: error_create failed with errno %d\n", errno);
                    return NULL;
                }
                LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Error_create failed with errno %d\n", errno);
                    return NULL;
                }
                parser->errors = head;

                parser->panic = true; // Set panic state to true
                return NULL;
            }

            Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (identifierToken == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the dot token
        }
        else
        {
            Token *operatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (operatorToken == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Token_create(parser->astArena, tokens, operatorToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the postfix operator token
        }
    }

    AstNode *postfixPrimeNode = astNode_create(parser->astArena, AST_POSTFIX_PRIME_EXPRESSION, tokens, children);
    if (postfixPrimeNode == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixPrimeExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return postfixPrimeNode;
}

AstNode *parser_parseArrayIndexingExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: No tokens available to parse array indexing expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_BRACKET)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '[' to start array indexing expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open bracket token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: No tokens available after open bracket.\n");
        return NULL;
    }

    AstNode *indexNode = parser_parseExpression(parser);
    if (indexNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: Panic state is true, skipping array indexing parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseArrayIndexingExpression: Failed to parse array index expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, indexNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: No tokens available after array index expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_BRACKET)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ']' to close array indexing expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close bracket token

    AstNode *arrayIndexingNode = astNode_create(parser->astArena, AST_ARRAY_INDEXING_EXPRESSION, NULL, children);
    if (arrayIndexingNode == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return arrayIndexingNode;
}

AstNode *parser_parseFunctionCallExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available to parse function call.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '(' to start function call.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after open parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: Panic state is true, skipping function call parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseFunctionCallExpression: Failed to parse function call expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after function call expression.\n");
            return NULL;
        }

        while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
        {
            parser->tokens = parser->tokens->next; // Move past the comma token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after comma.\n");
                return NULL;
            }

            expressionNode = parser_parseExpression(parser);
            if (expressionNode == NULL)
            {
                if (parser->panic)
                {
                    DEBUG_PRINT("parser_parseFunctionCallExpression: Panic state is true, skipping function call parsing.\n");
                    return NULL;
                }
                DEBUG_PRINT("parser_parseFunctionCallExpression: Failed to parse function call expression.\n");
                return NULL;
            }
            head = linkedList_Ast_create(parser->astArena, children, expressionNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;

            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after function call expression.\n");
                return NULL;
            }
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected ')' to close function call.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token

    AstNode *functionCallNode = astNode_create(parser->astArena, AST_FUNCTION_CALL_EXPRESSION, NULL, children);
    if (functionCallNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionCallNode;
}

AstNode *parser_parsePrimaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parsePrimaryExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parsePrimaryExpression: No tokens available to parse primary expression.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_IDENTIFIER && !parser_isLiteral(parser) && currentTokenType != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier, literal, or '(' to start primary expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *tokens = NULL;

    if (currentTokenType == TOKEN_IDENTIFIER)
    {
        Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
    }
    else if (parser_isLiteral(parser))
    {
        AstNode *literalNode = parser_parseLiteral(parser);
        if (literalNode == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: Failed to parse literal.\n");
            return NULL;
        }
        return literalNode; // Return the literal node directly instead of creating a primary expression
    }
    else if (currentTokenType == TOKEN_OPEN_PARENTHESIS)
    {
        parser->tokens = parser->tokens->next; // Move past the open parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: No tokens available after open parenthesis.\n");
            return NULL;
        }

        AstNode *groupedExprNode = parser_parseExpression(parser);
        if (groupedExprNode == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: Failed to parse grouped expression.\n");
            return NULL;
        }

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: No tokens available after grouped expression.\n");
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the close parenthesis token
        return groupedExprNode; // Return the grouped expression node instead of creating a primary expression
    }

    AstNode *primaryExpressionNode = astNode_create(parser->astArena, AST_PRIMARY_EXPRESSION, tokens, NULL);
    if (primaryExpressionNode == NULL)
    {
        DEBUG_PRINT("parser_parsePrimaryExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return primaryExpressionNode;
}

// --------------------------------------------------------------------------------

void parser_recoverSymbolPanic(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_recoverSymbolPanic: Parser is NULL.\n");
        return;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_recoverSymbolPanic: No tokens available to recover from panic.\n");
        return;
    }

    // Skip tokens until we find a token that can start a new symbol
    while (parser->tokens != NULL && ((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_EXPORT &&
           ((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        parser->tokens = parser->tokens->next;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_recoverSymbolPanic: Reached end of tokens while recovering from panic.\n");
        return;
    }

    // Reset panic state
    parser->panic = false;
}

AstNode *parser_parseProgramSymbols(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseProgramSymbols: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseProgramSymbols: No tokens available to parse global symbols.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    while (((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_EXPORT)
        {
            parser->tokens = parser->tokens->next; // Move to the next token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseProgramSymbols: No tokens available after moving to next token.\n");
                return NULL;
            }
        }
        else
        {
            if (parser->tokens->next == NULL)
            {
                DEBUG_PRINT("parser_parseProgramSymbols: No tokens available after export keyword.\n");
                return NULL;
            }
            My_TokenType currentTokenType = ((Token *)parser->tokens->next->data)->type;
            if (currentTokenType == TOKEN_OPEN_PARENTHESIS)
            {
                AstNode *function = parser_parseFunctionDefinitionSymbol(parser);
                if (function == NULL)
                {
                    if (parser->panic) goto parser_programBodySymbolPanic_Label;
                    DEBUG_PRINT("parser_parseProgram: Failed to parse function symbol.\n");
                    return NULL;
                }
                LinkedList *head = linkedList_Ast_create(parser->astArena, children, function);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                    return NULL;
                }
                children = head;
            }
            else if (currentTokenType == TOKEN_KEYWORD_STRUCT)
            {
                AstNode *structDeclaration = parser_parseStructDeclarationSymbol(parser);
                if (structDeclaration == NULL)
                {
                    if (parser->panic) goto parser_programBodySymbolPanic_Label;
                    DEBUG_PRINT("parser_parseProgram: Failed to parse struct declaration symbol.\n");
                    return NULL;
                }
                LinkedList *head = linkedList_Ast_create(parser->astArena, children, structDeclaration);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                    return NULL;
                }
                children = head;
            }
            else if (currentTokenType == TOKEN_KEYWORD_UNION)
            {
                AstNode *unionDeclaration = parser_parseUnionDeclarationSymbol(parser);
                if (unionDeclaration == NULL)
                {
                    if (parser->panic) goto parser_programBodySymbolPanic_Label;
                    DEBUG_PRINT("parser_parseProgram: Failed to parse union declaration symbol.\n");
                    return NULL;
                }
                LinkedList *head = linkedList_Ast_create(parser->astArena, children, unionDeclaration);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                    return NULL;
                }
                children = head;
            }
            else if (currentTokenType == TOKEN_KEYWORD_ENUM)
            {
                AstNode *enumDeclaration = parser_parseEnumDeclarationSymbol(parser);
                if (enumDeclaration == NULL)
                {
                    if (parser->panic) goto parser_programBodySymbolPanic_Label;
                    DEBUG_PRINT("parser_parseProgram: Failed to parse enum declaration symbol.\n");
                    return NULL;
                }
                LinkedList *head = linkedList_Ast_create(parser->astArena, children, enumDeclaration);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                    return NULL;
                }
                children = head;
            }
            else if (parser_isFullType(parser))
            {
                AstNode *globalDeclaration = parser_parseGlobalVariableDeclarationSymbol(parser);
                if (globalDeclaration == NULL)
                {
                    if (parser->panic) goto parser_programBodySymbolPanic_Label;
                    DEBUG_PRINT("parser_parseProgram: Failed to parse global declaration symbol.\n");
                    return NULL;
                }
                LinkedList *head = linkedList_Ast_create(parser->astArena, children, globalDeclaration);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                    return NULL;
                }
                children = head;
            }
            else
            {
                Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->next->data)->location, "Unexpected token after export keyword.");
                if (error == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: error_create failed with errno %d\n", errno);
                    return NULL;
                }
                LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with errno %d\n", errno);
                    return NULL;
                }
                parser->errors = head;
                parser->panic = true; // Set panic state to true
            }

            parser_programBodySymbolPanic_Label:
            if(parser->panic) parser_recoverSymbolPanic(parser);
            if (parser->panic) return NULL; // If panic state is true, return NULL
            if (parser->tokens->next == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: No tokens available after processing current token.\n");
                return NULL;
            }
        }
    }

    AstNode *program = astNode_create(parser->astArena, AST_PROGRAM, NULL, children);
    if (program == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return program;
}

AstNode *parser_parseFunctionDefinitionSymbol(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available to parse function definition symbol.\n");
        return NULL;
    }
    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after export keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_EXPORT && ((Token *)parser->tokens->next->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'export' then '(' to start function definition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic state to true
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the export token
    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *functionReturnParameterListNode = parser_parseReturnParameterList(parser);
    if (functionReturnParameterListNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: Panic state is true, skipping function definition parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: Failed to parse return parameter list.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, functionReturnParameterListNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after return parameter list.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected close parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after close parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected function name after close parenthesis.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *functionNameToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (functionNameToken == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, functionNameToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the function name token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after function name.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected open parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *functionParameterListNode = parser_parseFunctionParameterList(parser);
    if (functionParameterListNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: Panic state is true, skipping function definition parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: Failed to parse function parameter list.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, functionParameterListNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;
    
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after function parameter list.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected close parenthesis after function parameter list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *functionDefinitionNode = astNode_create(parser->astArena, AST_FUNCTION_DEFINITION, tokens, children);
    if (functionDefinitionNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinitionSymbol: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionDefinitionNode;
}

AstNode *parser_parseStructDeclarationSymbol(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: No tokens available to parse.\n");
        return NULL;
    }
    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: No tokens available after export keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_EXPORT && ((Token *)parser->tokens->next->data)->type != TOKEN_KEYWORD_STRUCT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'export' then 'struct' keyword for struct declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the export token
    parser->tokens = parser->tokens->next; // Move past the struct token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: No tokens available after struct keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after struct keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: No tokens available after struct identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' after struct identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *members = parser_parseStructUnionMemberDeclaration(parser);
    if (members == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseStructDeclarationSymbol: Panic state is true, skipping struct declaration parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: Failed to parse struct members declaration symbols.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, members);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: No tokens available after struct members declaration.\n");
        return NULL;
    }

    AstNode *structNode = astNode_create(parser->astArena, AST_STRUCT_DECLARATION, tokens, children);
    if (structNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclarationSymbol: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structNode;
}

AstNode *parser_parseGlobalVariableDeclarationSymbol(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available to parse variable global declaration.\n");
        return NULL;
    }
    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available after export keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected a full type for global variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }
    
    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the export token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available after export keyword.\n");
        return NULL;
    }

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: Panic state is true, skipping global variable declaration parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in global variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true;
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available after comma.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_EXPORT)
        {
            Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (exportToken == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Token_create(parser->astArena, tokens, exportToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the export token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available after export keyword.\n");
                return NULL;
            }
        }

        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            if (parser->panic)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: Panic state is true, skipping global variable declaration parsing.\n");
                return NULL;
            }
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: Failed to parse full type after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available to parse global variable declaration.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after type in global variable declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->panic = true;
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: No tokens available after additional identifier.\n");
            return NULL;
        }
    }

    AstNode *globalVariableDeclarationNode = astNode_create(parser->astArena, AST_GLOBAL_VARIABLE_DECLARATION, tokens, children);
    if (globalVariableDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclarationSymbol: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return globalVariableDeclarationNode;
}

AstNode *parser_parseEnumDeclarationSymbol(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: No tokens available to parse enum declaration.\n");
        return NULL;
    }
    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: No tokens available after export keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_EXPORT && ((Token *)parser->tokens->next->data)->type != TOKEN_KEYWORD_ENUM)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'export' then 'enum' keyword to start enum declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the export token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: No tokens available after export keyword.\n");
        return NULL;
    }
    
    parser->tokens = parser->tokens->next; // Move past the enum keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: No tokens available after enum keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after 'enum' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' to start enum body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *enumValueDeclarationNode = parser_parseEnumValueDeclarationSymbol(parser);
    if (enumValueDeclarationNode == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseEnumDeclarationSymbol: Panic state is true, skipping enum declaration parsing.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: Failed to parse enum value declaration symbol.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, enumValueDeclarationNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: No tokens available after enum value declaration.\n");
        return NULL;
    }

    AstNode *enumDeclarationNode = astNode_create(parser->astArena, AST_ENUM_DECLARATION, tokens, children);
    if (enumDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclarationSymbol: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return enumDeclarationNode;
}

AstNode *parser_parseUnionDeclarationSymbol(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: No tokens available to parse.\n");
        return NULL;
    }
    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: No tokens available after export keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_EXPORT && ((Token *)parser->tokens->next->data)->type != TOKEN_KEYWORD_UNION)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected 'export' then 'union' keyword for union declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the export token
    parser->tokens = parser->tokens->next; // Move past the union token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: No tokens available after union keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier after union keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: No tokens available after union identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected '{' after union identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->panic = true; // Set panic mode to true
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *members = parser_parseStructUnionMemberDeclaration(parser);
    if (members == NULL)
    {
        if (parser->panic)
        {
            DEBUG_PRINT("parser_parseUnionDeclarationSymbol: Panic state is true, skipping union declaration.\n");
            return NULL;
        }
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: Failed to parse union member declaration.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, members);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *unionNode = astNode_create(parser->astArena, AST_UNION_DECLARATION, tokens, children);
    if (unionNode == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclarationSymbol: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return unionNode;
}

AstNode *parser_parseEnumValueDeclarationSymbol(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: No tokens available to parse enum value declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->location, "Expected identifier for enum value.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->panic = true; // Set panic mode to skip further parsing
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type != TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past until comma
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: No tokens available after comma.\n");
            return NULL;
        }
    }

    parser->tokens = parser->tokens->next; // Move past the comma token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: No tokens available after comma.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
    {
        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: No tokens available after identifier.\n");
            return NULL;
        }

        while (((Token *)parser->tokens->data)->type != TOKEN_COMMA)
        {
            parser->tokens = parser->tokens->next; // Move past until comma
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: No tokens available after comma.\n");
                return NULL;
            }
        }

        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: No tokens available after comma.\n");
            return NULL;
        }
    }

    AstNode *enumValueDeclarationNode = astNode_create(parser->astArena, AST_ENUM_VALUE_DECLARATION, tokens, children);
    if (enumValueDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclarationSymbol: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return enumValueDeclarationNode;
}

// --------------------------------------------------------------------------------

Parser *parser_create(Arena *utilsArena, Arena *astArena, LinkedList *tokens)
{
    if (utilsArena == NULL)
    {
        DEBUG_PRINT("parser_create: utilsArena is NULL.\n");
        return NULL;
    }

    if (astArena == NULL)
    {
        DEBUG_PRINT("parser_create: astArena is NULL.\n");
        return NULL;
    }

    if (tokens == NULL)
    {
        DEBUG_PRINT("parser_create: tokens is NULL.\n");
        return NULL;
    }

    Parser *parser = (Parser *)arena_alloc(utilsArena, sizeof(Parser), alignof(Parser));
    if (parser == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_create: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_create: arena_alloc failed with unknown error\n");
        }
        return NULL;
    }

    parser->utilsArena = utilsArena;
    parser->astArena = astArena;
    parser->errors = NULL; // Initialize errors list as NULL
    parser->tokens = tokens; // Set the provided tokens list
    parser->ast = NULL; // Initialize AST as NULL
    parser->panic = false; // Initialize panic state as false

    return parser;
}

void parser_parse(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parse: Parser is NULL.\n");
        return;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parse: No tokens to parse.\n");
        return;
    }

    AstNode *program = parser_parseProgram(parser);
    if (program == NULL)
    {
        DEBUG_PRINT("parser_parse: Failed to parse program.\n");
        return;
    }

    parser->ast = program;
}

void parser_parseGlobalSymbols(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalSymbols: Parser is NULL.\n");
        return;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalSymbols: No tokens to parse global symbols.\n");
        return;
    }

    AstNode *globalSymbols = parser_parseProgramSymbols(parser);
    if (globalSymbols == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalSymbols: Failed to parse global symbols.\n");
        return;
    }

    parser->ast = globalSymbols;
}

void parser_print(const Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_print: Parser is NULL.\n");
        return;
    }

    printf("Parser: {\n");
    printf("    utilsArena:\n");
    arena_print(parser->utilsArena);
    printf("    astArena:\n");
    arena_print(parser->astArena);
    printf("    tokens: ");
    if (parser->tokens == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        linkedList_print(parser->tokens, (PrintFunction)token_print);
    }
    printf("    ast: ");
    if (parser->ast == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        // Assuming ast_print is a function that prints the AST node
        astNode_printTree(parser->ast, "", false);
    }
    printf("}\n");
}