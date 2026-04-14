# bah-cil

> NOTE: This programming language is not intended for **PRODUCTION** at all. **DO NOT USE IN PRODUCTION ENVIRONMENT**.

## Project Structure
```
.
|-- build/       # Compiled binaries and object files
|-- docs/        # Compiler documentations, manuals, and specifications
|-- example/     # Sample code
|-- scripts/     # Build scripts and automation
|-- src/         # Implementation folder
|   |-- codegen/ # Target code generation (x86, ARM, and etc.)
|   |-- ir/      # Intermediate Representation definition / map
|   |-- lexer/   # Lexer / Tokenizer source code
|   |-- parser/  # Abstract Syntax Tree (AST) Parser source code
|   |-- utils/   # Utilities to help implementation
|   +-- main.c   # Compiler entrypoint
|-- tests/       # Unit & integration test
+-- Makefile     # Build system configuration
```
