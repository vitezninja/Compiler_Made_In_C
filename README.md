# Complier made in C - Cmc

## Summary  
Cmc is a cross-platform compiler for a C and GoLang like language.

## Project status  
Currently under develpoment.

## Features  
- Lexer with support for integer, float, string, char, hex/octal literals
- Recursive descent parser building a typed AST
- Type system with primitives and structs/unions/enums
- Token-based error reporting with context
- Debug logger with optional output redirection
- Planned: Semantic analysis & Intermediat representation & Code generation

## Getting Started  
### Prerequisites  
- C11-compatible GCC compiler 
- Make
- Windows, Linux or MacOs (cross-platform)  
### Building  
```bash
make release
```  
### Usage  
```bash
.\cmc [options] <source files>
```

## Documentation  
Read about it [here](docs/docs.md).

## Contributing  
Contributions welcome! Just open a PR or start a discussion if you're unsure where to begin.

## License  
MIT License – See [LICENSE](LICENSE) for details.
