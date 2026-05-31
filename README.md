# C Fundamentals

A hands-on exploration of C from the ground up — memory, pointers,
data structures, algorithms, and systems programming.

The goal is not just to write programs but to understand what happens
at the machine level. Every program here is written with that intent.

---

## Directory Structure

```
c-fundamentals/
├── standard_library_implementations/
│   ├── strlen.c
│   ├── memcpy.c
│   ├── memmove.c                         ← todo
│   ├── strcpy.c                          ← todo
│   ├── strcat.c                          ← todo
│   └── malloc.c                          ← todo (ambitious but impressive)
│
├── data_structures/
│   ├── linked_list.c                     ← todo
│   ├── doubly_linked_list.c              ← todo
│   ├── stack.c                           ← todo
│   ├── queue.c                           ← todo
│   ├── hash_map.c                        ← todo
│   └── dynamic_array.c                   ← todo
│
├── algorithms/
│   ├── bubble_sort.c                     ← todo
│   ├── insertion_sort.c                  ← todo
│   ├── binary_search.c                   ← todo
│   ├── merge_sort.c                      ← todo
│   ├── quick_sort.c                      ← todo
│   └── generic_sort.c                    ← todo
│
├── systems/
│   ├── file_programming/
│   ├── network_programming/
│   │   └── http_server/                 ← currently working on it
│   └── commandline_tools/
│
├── memory_and_pointers/
│   ├── pointer_arithmetic.c              ← todo
│   ├── struct_memory_layout.c            ← todo
│   ├── generic_functions.c               ← todo
│   └── function_pointers.c               ← todo
│
└── projects/
    ├── markdown_parser/
    └── brain_fuc*_interpreter/
```

---

## Standard Library Implementations

Reimplementing standard library functions from scratch to understand
what the abstractions are hiding.

| File | Description | Status |
|---|---|---|
| `strlen.c` | Counts bytes in a string by walking memory until `\0` | ✅ Done |
| `memcpy.c` | Copies n bytes from source to destination using void pointers | ✅ Done |
| `memmove.c` | Like memcpy but handles overlapping memory regions | 🔲 Todo |
| `strcpy.c` | Copies a string including the null terminator | 🔲 Todo |
| `strcat.c` | Concatenates two strings | 🔲 Todo |
| `malloc.c` | Simple memory allocator | 🔲 Todo |

---

## Data Structures

Implementing fundamental data structures using raw memory and pointers.

| File | Description | Status |
|---|---|---|
| `linked_list.c` | Singly linked list with insert, delete, search | 🔲 Todo |
| `doubly_linked_list.c` | Linked list that traverses both directions | 🔲 Todo |
| `stack.c` | LIFO data structure using linked list | 🔲 Todo |
| `queue.c` | FIFO data structure using linked list | 🔲 Todo |
| `hash_map.c` | Hash map with collision handling | 🔲 Todo |
| `dynamic_array.c` | Vector-like growable array using realloc | 🔲 Todo |

---

## Algorithms

| File | Description | Status |
|---|---|---|
| `bubble_sort.c` | Simple comparison sort |  🔲 Done |
| `insertion_sort.c` | Efficient for small or nearly sorted data | 🔲  Done |
| `binary_search.c` | O(log n) search on sorted arrays | 🔲 Done |
| `generic_sort.c` | Sorting any data type using void pointers and function pointers | 🔲 Done |
| `merge_sort.c` | Divide and conquer sorting | 🔲 Todo |
| `quick_sort.c` | The algorithm behind the standard library qsort | 🔲 Todo |

---

## Systems Programming

Programs that interact directly with the operating system.

### File I/O
Reading, writing, and parsing structured data from files.

### Network Programming

| File | Description | Status |
|---|---|---|
| `http_server.c` | Serves static files over TCP | 🔲 Done |
| `multithreaded_http_server.c` | Handles concurrent connections | 🔲 Todo |

### Command Line Tools
Tools that read from stdin, process data, and write to stdout.

---

## Memory and Pointers

Programs that demonstrate deep pointer and memory understanding.

| File | Description |
|---|---|
| `pointer_arithmetic.c` | Walking arrays and strings with pointer math |
| `struct_memory_layout.c` | Padding, alignment, and offsetof |
| `generic_functions.c` | Writing functions that work on any type using void pointers |
| `function_pointers.c` | Passing behavior as data |

---

## Parsers

| File | Description | Status |
|---|---|---|
| `markdown_parser.c` | Parses markdown and converts to HTML | 🔲 Todo |

The markdown parser is the most ambitious project in this repo — it
combines string handling, memory management, file I/O, and pointers
into one real, useful program.

---

## What I Learned

C forces you to think about things most languages hide:

- There are no strings — just pointers to bytes ending in `\0`
- There are no generics — you use void pointers and function pointers
- There is no automatic memory — you allocate and free manually
- Every abstraction has a cost you can measure and understand

This understanding carries into every other language and makes you
a better programmer regardless of what you write in.

---

## Build

Each program is self contained and compiles with:

```bash
gcc -Wall -Wextra -o output filename.c
```
