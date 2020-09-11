#include "../src/cpu.h"

#include <stdbool.h>
#include <stdio.h>

#include "../src/alu.h"

void ALU_test() {
    printf("----------------\n");
    printf("Testing ALU...\n");
    printf("----------------\n");
    int16_t x = 16;
    int16_t y = 25;

    // all 18 operations that the ALU can do
    struct {
        uint8_t op;
        int16_t res;
        char ex[6];
    } ops[] = {
        {OP_C0, 0, "0"},       {OP_C1, 1, "1"},       {OP_N1, -1, "-1"},
        {OP_CX, x, "x"},       {OP_CY, y, "y"},       {OP_FX, ~x, "~x"},
        {OP_FY, ~y, "~y"},     {OP_NX, -x, "-x"},     {OP_NY, -y, "-y"},
        {OP_IX, x + 1, "x+1"}, {OP_IY, y + 1, "y+1"}, {OP_DX, x - 1, "x-1"},
        {OP_DY, y - 1, "y-1"}, {OP_AD, x + y, "x+y"}, {OP_SY, x - y, "x-y"},
        {OP_SX, y - x, "y-x"}, {OP_AN, x & y, "x&y"}, {OP_OR, x | y, "x|y"}};

    printf("x: %d, y: %d\n", x, y);
    for (int i = 0; i < 18; ++i) {
        uint8_t status = ops[i].op;
        int16_t res = ALU(x, y, &status);

        printf("expected: %3s ", ops[i].ex);
        if (res == ops[i].res)
            printf("result: %3d\n", res);
        else
            printf("ALU ERROR :(\n");
    }
}

// test cpu
void CPU_test() {
    printf("----------------\n");
    printf("Testing CPU...\n");
    printf("----------------\n");
    struct CPU* cpu = new_cpu();
    int n = 0x0064;
    uint16_t sum_1_N[0x0013] = {0x0010, 0xefc8, 0x0011, 0xea88, 0x0010,
                                0xfc10, n,      0xe4d0, 0x0012, 0xe301,
                                0x0010, 0xfc10, 0x0011, 0xf088, 0x0010,
                                0xfdc8, 0x0004, 0xea87, 0x0012};

    // might need to find a way to halt this somehow
    while (cpu->PC < 0x0012) {
        execute(sum_1_N[cpu->PC], cpu);
    }
    printf("sum: %d i: %d\n", cpu->RAM[0x0011], cpu->RAM[0x0010]);

    clean_cpu(cpu);
}
int main() {
    ALU_test();
    CPU_test();
}