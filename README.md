# Midterm Project - Implement ls(1)

## Overview
This project implements a simplified, modular version of the UNIX `ls` command from scratch in C, strictly following the provided NetBSD manual page (`ls(1)`). It incorporates low-level system calls such as `opendir`, `readdir`, `lstat`, and proper permission/metadata parsing.

## Implemented Features & Options
- **Basic Listing**: Lists directory contents or specific file operands in lexicographical order.
- **`-a`**: Include directory entries whose names begin with a dot (`.`).
- **`-l`**: List in long format (file mode/permissions, number of links, owner name, group name, number of bytes, modification time, and pathname/symbolic link targets).
- **`-t`**: Sort by time modified (most recently modified first).
- **`-S`**: Sort by file size (largest file first).
- **`-r`**: Reverse the order of the sort.

## Project Structure (Modular Design)
- `main.c` / `main.h`: Command-line arguments parsing using `getopt()`.
- `ls_core.c` / `ls_core.h`: Core directory traversal, reading, and sorting coordination.
- `format.c` / `format.h`: Handles long format (`-l`) string generation and `lstat` metadata extraction.
- `sort.c` / `sort.h`: Implements comparators for name, time, and size sorting (`qsort`).
- `Makefile`: Automated compilation and clean rules.
- `.gitignore`: Excludes compiled binaries (`my_ls`) and object files (`*.o`).

## How to Compile & Run
1. Compile the project using Makefile:
   ```bash
   make
