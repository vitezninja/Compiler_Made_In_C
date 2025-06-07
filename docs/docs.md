I want to make a simple compiler in C (gcc-11 and gnu99) that compiles a language similar to C.
This project will not make its own assembly I will use NASM.
I want this program to work on Windows, Linux, Unix and MacOS.
I will use git as source controll and I will also use make for building the program on the priviously listed OS-s.
This project will be on github where it will use github actions automation.
I want to use external dependencys only when needed.

The project structure will be:
```
compiler
- .github/workflow/c-cpp.yml
- src/
-- main.c
-- options.c
-- lexer.c
-- parser.c
-- validator.c
-- codeGenerator.c
-- fileSystem.c
-- utils/
--- dataStructures/
---- hashTable.c
---- linkedList.c
---- bitset.c
---- stack.c
---- dynamicArray.c
--- logger.c
--- arena.c
--- ast.c
--- error.c
--- string.c
--- token.c
--- symbol.c
- test/
-- suits/
--- tes_options.c
--- test_lexer.c
--- test_parser.c
--- test_validator.c
--- test_codeGenerator.c
--- test_fileSystem.c
--- utils/
---- dataStructures/
----- test_hashTable.c
----- test_linkedList.c
----- test_bitset.c
----- test_stack.c
----- test_dynamicArray.c
---- test_arena.c
---- test_ast.c
---- test_error.c
---- test_string.c
---- test_token.c
---- test_symbol.c
-- tester.c
-- test_script.sh
-- test_script.bat
- build/ (same structure as in src)
- include/ (contains all the .h files only separating utils/ into its own directory)
- Makefile
- .gitignore
- README.md
- LICENSE (MIT License)
```

Done:
   .github/workflow/c-cpp.yml
   Makefile
   .gitignore
   LICENSE
   logger.c/h + documentation
   arena.c/h + documentation
   ast.c/h + documentation
   bitset.c/h + documentation
   error.c/h + documentation
   linkedList.c/h + documentation
   my_string.c/h + documentation
   symbols.c/h + documentation
   token.c/h + documentation
   options.c/h + documentation
   hashTable.c/h + documentation

Making this now:
   fileSystem.c/h + documentation

Todo:
   Fix includes
   Make test files
   Decide how to handel NULL (is it a keyword or identifier or literal)

   stack.c/h + documentation
   dynamicArray.c/h + documentation
   lexer.c/h documentation
   parser.c/h + documentation
   validator.c/h + documentation
   codeGenerator.c/h + documentation

Testing will be done with runing the test_script. This will compile the files needed for testing then run them then clean up there files.

## Memory managment:
For now I have only made plans until the parsing is finished.
I will have 2 arenas. For easier explanation I will call them Alpha, Beta. (Maybe I will need more)
There will be also another arena for string inturning but i will leave that one out as it will have full lifetime.
Important rule is that if I have errors at any point I will stop compilation.
Errors are a linkedList when I refer to storing them I also mean that as a linkedList.

(Here could be a part for handeling the command line arguments and a loop to handle multiple files)

### Step 1 (file reading):
1. Create Alpha.
2. Store data like fileSystem and any error that occure during this process in Aplha.
3. File contents won't be stored in an arena this will be needed for error messages so it needs to have full lifetime during the whole compilation.
   This will also not need realloc so a normal malloc is perfectly fine.

Memory summery:
Alpha has content
Beta is empty

### Step 2 (lexing):
1. Create the lexer and store it in Alpha.
2. Create Beta.
3. Lex the file contents and create tokens into a linkedList that will have its memory in Beta.
4. Any errors that occure during process will be stored in Alpha.
5. Clear Alpha after lexing.

Memory summery:
Alpha is empty
Beta has content

### Step 3 (parsing):
1. Create the parser and store it in Beta.
2. Parse the tokens in Beta.
   This will create an AST that will be stored in Alpha as well as copy any tokens that are neccecery for the AST.
   Meaning identifiers, keywords (not all, as keywords like IF are already referd to in AST), literals.
3. Any errors that occure during process will be stored in Beta.
4. Clear Beta.

Memory summery:
Alpha has content
Beta is empty

### Step 4 (validation): This is not made yet
1. Create the validator into Beta.
2. Create symbol table (hash table + linkedList) in Beta.
3. Constant fold the AST. If this creates new AST node or tokens store them in Alpha.
4. Validate the AST.
5. ?
x. Any errors that occure during this process will be stored in Beta.
x. Clear Beta.

(Maybe make IR)

Memory summery:
Alpha has content
Beta is empty

### Step 5 (code generation): This is not made yet
1. Create the code generator into Beta.
2. Create fileSystem into Beta.
3. Generate NASM code from the AST.
4. Write the NASM code into files with fileSystem.
5. ?
x. Clear Alpha.
x. Clear Beta.

Memory summery:
Alpha ?
Beta ?