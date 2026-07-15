# Invoicing System (IAED)

A command-line invoicing system developed in C for the IAED course (2025/2026) at Instituto Superior Técnico (IST)

### Evaluation
* Automated Assessment: 75/80
* Manual Code Review: 4/4

### Project Features
* Product and Cart Management: Supports up to 10,000 products, EAN-8/13 check-digit validation, and real-time billing with VAT
* Pattern Matching: Custom search algorithm using wildcards (* and ?)[span_4](start_span)[span_4](end_span).
* Memory-Optimized: Built with dynamic memory allocation, zero global variables, and fully validated with Valgrind[span_5](start_span)[span_5](end_span).
* Strict Constraints: No use of "goto", "extern", or native "qsort[span_6](start_span)"[span_6](end_span).

---

## Compilation

Compile the project with the following flags[span_7](start_span)[span_7](end_span):
```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj *.c


