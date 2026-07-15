# Invoicing System (IAED)

A command-line invoicing system developed in C for the IAED course (2025/2026) at Instituto Superior Técnico (IST)

### Evaluation
* Automated Assessment: 75/80
* Manual Code Review: 4/4

### Project Features
* Product and Cart Management: Supports up to 10,000 products, EAN-8/13 check-digit validation, and real-time billing with VAT
* Pattern Matching: Custom search algorithm using wildcards (* and ?)
* Memory-Optimized: Built with dynamic memory allocation, zero global variables, and fully validated with Valgrind
* Strict Constraints: No use of `goto"`, `extern"`, or native `qsort`

### Compilation

Compile the project with the following flags
```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj *.c
```
### Run
```bash
./proj
```
