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
│   ├── singly_linked_list.c
│   ├── doubly_linked_list.c
│   ├── circular_linked_list.c
│   ├── stack.c                           ← todo
│   ├── queue.c                           ← todo
recursion
trees
sorting_algorithmes
searching_algorithmes
grapsh
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

## Build

Each program is self contained and compiles with:

```bash
gcc -Wall -Wextra -o output filename.c
```
