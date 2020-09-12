#ifndef _CPU_H_
#define _CPU_H_

#include <stdint.h>

#define MAX_MEM 0x6001

struct CPU {
    // registers for use with the ALU
    uint16_t A;
    uint16_t D;
    uint16_t PC;
    uint16_t* RAM;
};

int16_t ALU(int16_t x, int16_t y, uint8_t* status);

struct CPU* new_cpu();
void delete_cpu(struct CPU* cpu);

void print_cpu(struct CPU* cpu);

void execute(uint16_t instruction, struct CPU* cpu);

#endif