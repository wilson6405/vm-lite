#include <stdbool.h>
#include <stdio.h>

typedef enum {
    PUSH,
    ADD,
    SUB,
    POP,
    SET,
    HLT,
    INSTR_SIZE
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

extern inline void
add(void)
{
    registers[A] = stack[SP--];
    registers[B] = stack[SP--];

    registers[C] = registers[B] + registers[A];

    stack[++SP] = registers[C]; // increase stack pointer first
}

extern inline void
subtraction(void)
{
    registers[A] = stack[SP--];
    registers[B] = stack[SP--];

    registers[C] = registers[A] - registers[B];

    stack[++SP] = registers[C];
}

extern inline void
push(void)
{
    stack[++SP] = program[++IP];
}

extern inline void
pop(void)
{
    int val_popped = stack[SP--];
    printf("popped %d\n", val_popped);
}

extern inline void
halt(void)
{
    running = false;
}

static void (*instr_handlers[INSTR_SIZE])(void) = {
    [ADD]  = add,
    [SUB]  = subtraction,
    [PUSH] = push,
    [POP]  = pop,
    [HLT]  = halt,
};

int
main()
{
    while (running) {
        instr_handlers[fetch()]();
        IP++; // Next instruction
    }

    return 0;
}
