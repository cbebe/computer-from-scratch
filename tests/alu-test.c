#include <stdint.h>
#include <stdio.h>

#include "cpu.h"

typedef struct {
    uint8_t op;
    int16_t res;
    char ex[6];
} operations;

int main() {
    int16_t x = 16;
    int16_t y = 25;

    // all 18 operations that the ALU can do

    operations ops[] = {
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

    return 0;
}
