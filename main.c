#include <stdbool.h>
#include <stdio.h>

typedef enum instruction_set {
    PUSH,
    ADD,
    POP,
    SET,
    HLT
} Instructions;

const int program[] = {
    PUSH, 5,
    PUSH, 6,
    ADD,
    POP,
    HLT
};

int ip = 0; // Instruction pointer
int sp = -1; // stack pointer
int stack[256];
bool running = true;

int
fetch()
{
    return program[ip];
}

void
eval(int instr)
{
    switch (instr) {
        case ADD: {
            int a = stack[sp--];
            int b = stack[sp--];

            int result = b + a;
            sp++;
            stack[sp] = result;

            break;
        }

        case PUSH: {
            sp++;
            stack[sp] = program[++ip];
            break;
        }

        case POP: {
            int val_popped = stack[sp--];
            printf("popped %d\n", val_popped);
        }

        case HLT: {
            running = false;
            break;
        }
    }
}

int
main()
{
    while (running) {
        eval(fetch());
        ip++;
    }

    return 0;
}


