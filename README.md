# Compiler Made in C

**Compiler Made in C** is a simple yet powerful compiler designed to process and analyze C-style languages. This project aims to provide a foundational compiler framework in C, capable of tokenizing input source code and processing various language constructs.

## Current Status

This project is currently under active development. At the moment, only the Lexer is implemented and available. The lexer is responsible for tokenizing input text into a sequence of tokens. 

Future plans for the compiler include:

- Implementing a parser to analyze token sequences.
- Adding a code generator to produce executable code.
- Implementing semantic analysis and optimizations.

Stay tuned for updates as more components are developed and integrated into the compiler.

## Current Features

- **Lexer:** Implements a lexical analyzer to parse and tokenize C-style language constructs into tokens.

## Grammer

The grammer that this compiler translates can be found in the [Grammer](grammer.md).

## Usage

### Building the Project

To build the project, run:

1. **Clone the repository:**
   ```sh
   git clone https://github.com/vitezninja/Compiler_Made_In_C.git
   cd compiler-made-in-c
   ```

2. **Compile the source code:**  
- **On Linux/macOS**:
    ```bash
    make lin
    ```

- **On Windows**:
    Use a tool like MinGW or a similar environment that supports `make`. You might need to install it separately and then use:
    ```bash
    mingw32-make
    ```

### Running the Compiler

After building the project, you can run the compiler:

- **On Linux/macOS**:
    ```bash
    ./main.out
    ```

- **On Windows**:
    ```bash
    main.exe
    ```

### Testing the Compiler

The compiler processes input source code and tokenizes it into a series of tokens. You can modify the `input` string in `main.c` to test different inputs.

- **Basic Test**:
    ```c
    char* input = "int main() { return 0; }";
    ```

- **Complex Test**:
    ```c
    char* input = """
    int main() 
    { 
        /* this is a comment */
        int x = 42;
        // another comment\r\n
    }
    """;
    ```
## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/new-feature`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature/new-feature`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

