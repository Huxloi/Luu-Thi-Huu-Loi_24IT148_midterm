# Midterm Project - Implement ls(1)

## 1. Project Overview
This project implements a modular, robust subset of the UNIX `ls` command (`ls(1)`) from scratch in the C programming language, adhering strictly to the NetBSD manual specifications[cite: 24]. It is engineered to handle filesystem traversal, low-level metadata parsing, and comprehensive formatting options safely and efficiently.

## 2. Complete Options Reference & Explanations
The program supports and implements the behavior for the following options as defined in the NetBSD `ls(1)` manual page[cite: 22, 23]:

- **`-A`**: List all entries except for `.` and `..`[cite: 22].
- **`-a`**: Include directory entries whose names begin with a dot (`.`), exposing hidden files[cite: 22].
- **`-c`**: Use time when file status was last changed (`ctime`) instead of modification time (`mtime`) for sorting (`-t`) or printing (`-l`)[cite: 22].
- **`-d`**: Directories are listed as plain files (not searched recursively)[cite: 22].
- **`-F`**: Display a type suffix after each pathname (`/` for directories, `*` for executables, `@` for symbolic links, etc.)[cite: 22].
- **`-f`**: Output is not sorted (turns on `-a` and disables sorting for high-speed scanning)[cite: 22].
- **`-h`**: Modifies `-s` and `-l` options, causing file sizes to be reported in human-readable bytes (e.g., 1K, 23M)[cite: 22].
- **`-i`**: Print each file's file serial number (inode number)[cite: 22].
- **`-k`**: Modify `-s` to report sizes in kilobytes (KB)[cite: 22].
- **`-l`**: (Lowercase letter "ell"). List in long format (file mode, links, owner, group, size, date, and pathname)[cite: 22, 24].
- **`-n`**: Same as `-l`, except owner and group IDs are displayed numerically rather than converted to names[cite: 22].
- **`-q`**: Force printing of non-printable characters in file names as `?`[cite: 22].
- **`-R`**: Recursively list subdirectories encountered[cite: 22].
- **`-r`**: Reverse the order of the sort (reverse lexicographical or oldest/smallest first)[cite: 22].
- **`-S`**: Sort by file size, largest file first[cite: 22].
- **`-s`**: Display the number of file system blocks actually used by each file, along with a `total` sum line[cite: 22].
- **`-t`**: Sort by modification time (most recently modified first)[cite: 23].
- **`-u`**: Use time of last access (`atime`) instead of modification time for sorting or printing[cite: 23].
- **`-w`**: Force raw printing of non-printable characters[cite: 23].

## 3. Technical Architecture & System Calls
- **Filesystem Traversal**: Uses low-level system calls `opendir()`, `readdir()`, and `closedir()`.
- **Metadata Extraction**: Utilizes `lstat()` to retrieve file permissions, links, UID/GID, sizes, and timestamps without following symbolic links.
- **Memory Management**: Employs dynamic memory allocation (`malloc`, `realloc`) to handle arbitrary directory sizes safely.

## 4. Project Structure (Modular Design)
- `main.c` / `main.h`: Argument parsing and option flag management via `getopt()`.
- `ls_core.c` / `ls_core.h`: Core directory scanning, filtering, and recursive coordination.
- `format.c` / `format.h`: Long format rendering (`-l`), permission string decoding (`strmode`), and human-readable size utilities.
- `sort.c` / `sort.h`: Sorting comparators for name, time (`-t`), and size (`-S`) using `qsort()`.
- `Makefile`: Automated compilation and clean rules.
- `.gitignore`: Excludes binary outputs (`my_ls`) and object files (`*.o`).

## 5. How to Compile & Run
1. Compile the project:
   ```bash
   make
