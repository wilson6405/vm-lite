#include <stdbool.h>
#include <stdio.h>

typedef enum {
    PUSH,
    ADD,
    SUB,
    POP,
    SET,
    HLT
} Instructions;

typedef enum {
    A, B, C, D, E, F, // General register
    INSTR_PTR,        // Instruction pointer
    STK_PTR,          // Stack pointer
    REGISTER_SIZE
} Registers;

static int registers[REGISTER_SIZE] = {[STK_PTR] = -1};

const int program[] = {
    PUSH, 5,
    PUSH, 6,
    ADD,
    POP,
    PUSH, 31,
    PUSH, 100,
    SUB,
    POP,
    HLT
};

#define STACK_SIZE 256
int stack[STACK_SIZE];
bool running = true;

#define IP registers[INSTR_PTR]
#define SP registers[STK_PTR]

int
fetch()
{
    return program[IP];
}

void
eval(int instr)
{
    switch (instr) {
        case ADD: {
            registers[A] = stack[SP--];
            registers[B] = stack[SP--];

            registers[C] = registers[B] + registers[A];

            stack[++SP] = registers[C]; // increase stack pointer first
            break;
        }

        case SUB: {
            registers[A] = stack[SP--];
            registers[B] = stack[SP--];

            registers[C] = registers[A] - registers[B];

            stack[++SP] = registers[C];
            break;
        }

        case PUSH: {
            stack[++SP] = program[++IP];
            break;
        }

        case POP: {
            int val_popped = stack[SP--];
            printf("popped %d\n", val_popped);
            break;
        }

        case HLT: {
            running = false;
            break;
        }
    }

    IP++; // Next instruction
}

int
main()
{
    while (running) {
        eval(fetch());
    }

    return 0;
}
