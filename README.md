# Compiler Made in C  
**Compiler Made in C** is a simple yet powerful compiler designed to process and analyze C-style languages. This project aims to provide a foundational compiler framework in C, capable of tokenizing input source code and processing various language constructs.

## Current Status  
This project is currently under active development.

Future plans for the compiler include:  
- Implementing semantic analysis and optimizations.
- Adding a code generator to produce executable code.

Stay tuned for updates as more components are developed and integrated into the compiler.

## Current Features  
- **Lexer:** Implements a lexical analyzer to parse and tokenize C-style language constructs into tokens.
- **Parser:** Analyzes the tokenized input to builds an Abstract Syntax Tree.
- **Virtual Machine:** Executes the compilation steps.

## Grammar  
The grammer that this compiler translates can be found in the [Grammar](grammar.md).

## Usage

### Building the Project  
To build the project, run:

1. **Clone the repository:**  
   ```sh
   git clone https://github.com/vitezninja/Compiler_Made_In_C.git
   cd compiler-made-in-c
   ```

2. **Compile the source code:**  
    ```bash
    make
    ```  
    or  
    ```bash
    mingw32-make
    ```  

### Running the Compiler  
After building the project, you can run the compiler:

- **On Linux/macOS**:
    ```bash
    ./cmc.out [options] file...
    ```

- **On Windows**:
    ```bash
    cmc.exe [options] file...
    ```

### Testing the Compiler  
The compiler processes input source code and tokenizes it into a series of tokens.  
Files to test the compiler on can be found in the tests directory, but feel free to create your own test file and test it on it.

### Removing the Compiler  
```bash
make clean
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

