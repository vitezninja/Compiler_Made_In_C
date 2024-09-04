#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdlib.h>
#include "../utils/file_reading.h"
#include "../utils/token.h"
#include "../Lexer/lexer.h"
#include "../Parser/parser.h"
#include "../utils/AST.h"

int runVM(int argc, char **argv);

#endif // VM_H