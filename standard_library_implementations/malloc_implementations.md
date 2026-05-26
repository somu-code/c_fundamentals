/*
Yes, very tricky. It is one of the hardest things you can implement in C because you are not just writing C code anymore — you are talking directly to the **operating system**.

## Why it is hard

**1. You need to ask the OS for memory**

`malloc` itself does not magically create memory. It calls OS system calls to get raw memory from the kernel:

- `sbrk()` — old way, moves the end of the heap up
- `mmap()` — modern way, maps a region of memory

So your `malloc` implementation needs to call one of these.

**2. You need to track allocations yourself**

You need to remember:
- Where each allocated block starts
- How big each block is
- Whether each block is free or in use

Typically done with a **linked list of block headers** sitting in the memory itself.

**3. You need to handle fragmentation**

When memory is freed, you get holes. A good malloc finds and reuses those holes instead of always asking the OS for more memory.

**4. Thread safety**

Real `malloc` handles multiple threads safely. Your simple version does not need to but real ones do.

## What a simple implementation looks like conceptually

```
heap memory:
[header|data....][header|data........][header|data..]
   ↑                  ↑                    ↑
   block 1            block 2              block 3
   (free)             (in use)             (free)
```

Each block has a hidden header storing its size and whether it is free.

## My honest suggestion

It is absolutely worth doing — it is the most impressive thing in your repo by far. But do it **after** you finish the data structures. You will need to understand linked lists well before tackling malloc.
