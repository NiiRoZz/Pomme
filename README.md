# Pomme

![pomme](./assets/apple.png)

Scripting language.

Target to be easily moddable and added to any application.

Used in a custom project for UE4.

## Components

### Lexer/Parser

Using [javacc](https://github.com/javacc/javacc) for generating the AST tree.

### Compiler

Convert pomme file into bytecode.

### Virtual Machine

Load bytecode produced by the [compiler](#Compiler).
Can instantiate a new class directly from your host application.