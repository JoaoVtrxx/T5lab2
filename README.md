# Course and Student Registry — C

Pair assignment for **Laboratório de Programação II, 2024/2**. A terminal application for managing courses and their students, using a binary search tree for courses and linked lists for enrolled students.

## Features

- Insert, remove and list courses.
- Insert and remove students associated with a course.
- List a course's students and print course/student relationships.

The menu and prompts are in Brazilian Portuguese. Data is held in memory during execution.

## Build and run

Requires a C compiler such as GCC. Build from source rather than relying on the existing `saida` executable, which may be specific to the original environment.

```bash
git clone https://github.com/JoaoVtrxx/T5lab2.git
cd T5lab2
gcc -Wall -Wextra main.c curso.c lista.c -o cadastro
./cadastro
```

Choose an option from the numbered menu; option **8** exits. Register a course before adding its students.

## Code map

| Files | Purpose |
| --- | --- |
| [main.c](main.c) | Menu and operation dispatch |
| [curso.c](curso.c) / [curso.h](curso.h) | Course tree and its operations |
| [lista.c](lista.c) / [lista.h](lista.h) | Student lists and course associations |

This repository preserves the original coursework implementation.
