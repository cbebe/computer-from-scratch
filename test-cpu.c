#include <stdio.h>

#include "cpu.h"

int main() {
    struct CPU *cpu = new_cpu();
    for (int i = 0; i < 1000000; i++) {
        for (int j = 0; j < 1000000; j++) {
            cpu->RAM[0] = 1;
            printf("%d", cpu->RAM[0]);
        }
    }
}