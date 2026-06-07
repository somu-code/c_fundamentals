# Brainfuck Interpreter

A simple Brainfuck interpreter written in C.

## What is Brainfuck?

[Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) is a minimalist esoteric programming language that operates on an array of memory cells (the "tape") using only 8 commands.

## Commands

| Command | Description |
|---------|-------------|
| `>` | Move data pointer right |
| `<` | Move data pointer left |
| `+` | Increment current cell |
| `-` | Decrement current cell |
| `.` | Output current cell as ASCII character |
| `,` | Read one character from stdin into current cell |
| `[` | Jump past matching `]` if current cell is zero |
| `]` | Jump back to matching `[` if current cell is non-zero |

Any character that is not one of the above is ignored (treated as a comment).

## Building

```
gcc -Wall -Wextra -std=c23 -pedantic -o bf interpreter.c
```

## Usage

```
./bf <source_file>
```

Example:

```
./bf hello_world_in_brain_fuc*.bf
```

## Constraints

- Tape size: 30,000 cells
- Max source file size: 30,000 bytes
- Tape cells are unsigned 8-bit (0–255), wrapping on overflow

## Error Handling

The interpreter reports errors for the following cases:

- No source file provided
- Too many arguments
- File not found or unreadable
- Empty source file
- Source file too large
- Tape pointer moved out of bounds
- Unmatched `[` or `]` in source file
