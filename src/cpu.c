#include "cpu.h"

#include <stdint.h>
#include <stdio.h>

// macro to extract a single bit from a field
#define bit(field, bit) (field & (1 << bit)) >> bit

int16_t ALU(int16_t x, int16_t y, uint8_t* status) {
    uint8_t cbits = *status;

    // zero out inputs
    if (bit(cbits, ZX)) x = 0;
    if (bit(cbits, ZY)) y = 0;

    // flip inputs
    if (bit(cbits, NX)) x = ~x;
    if (bit(cbits, NY)) y = ~y;

    // perform operation
    int16_t and = x & y;
    int16_t add = x + y;
    uint8_t fn = bit(cbits, FN);
    int16_t res = fn ? add : and;

    // flip output
    if (bit(cbits, NO)) res = ~res;

    // set or clear flags
    *status &= ~(F_ZR | F_NG);
    if (res == 0) *status |= F_ZR;
    if (res < 0) *status |= F_NG;

    return res;
}

// determines whether the instruction is an A or C instruction
enum { INSTRUCTION_BIT = 1 << 15 };
// bit masks for decoding c-instruction
enum { COMP_MASK = 0x1FC0, DEST_MASK = 0x38, JUMP_MASK = 0x7 };
// destination for memory
enum { MEM_DEST = 1 << 0, DAT_DEST = 1 << 1, ADR_DEST = 1 << 2 };
// conditions for jumping
enum { GT = 1 << 0, EQ = 1 << 1, LT = 1 << 2 };

void execute(uint16_t instruction, struct CPU* cpu) {
    if (instruction & INSTRUCTION_BIT) {
        // decode C-instruction
        uint8_t comp = (instruction & COMP_MASK) >> 6,
                dest = (instruction & DEST_MASK) >> 3,
                jump = (instruction & JUMP_MASK);

        // direct or indirect access on A register
        uint8_t mem_r = bit(comp, 6);
        int16_t a_access = mem_r ? cpu->RAM[cpu->A] : cpu->A;

        int16_t out = ALU(cpu->D, a_access, &comp);

        uint8_t zer_flag = bit(comp, ZR), neg_flag = bit(comp, NG);

        // move output to destination
        if (dest & MEM_DEST) cpu->RAM[cpu->A] = out;
        if (dest & DAT_DEST) cpu->D = out;
        if (dest & ADR_DEST) cpu->A = out;

        // jump program counter
        if ((neg_flag && (jump & LT)) || (!neg_flag && (jump & GT)) ||
            (zer_flag && (jump & EQ))) {
            cpu->PC = cpu->A;
            return;
        }
    } else {
        cpu->A = instruction;
    }

    ++cpu->PC;
}

void print_cpu(struct CPU* cpu) {
    printf("D register: %d\nA register: %d\nPC register: %d", cpu->D, cpu->A,
           cpu->PC);
}

// test cpu
int main() {
    struct CPU cpu;
    int n = 0x0005;
    uint16_t sum_1_N[] = {0x0001, 0xffc8, 0x0002, 0xfa88, 0x0001,
                          0xfc10, n,      0xe4d0, 0x0012, 0xe301,
                          0x0001, 0xfc10, 0x0002, 0xf088, 0x0001,
                          0xfdc8, 0x0005, 0xea87, 0x0000};

    int i = 0;
    while (i++ < 1000) {
        printf("%d ", cpu.PC);
        execute(sum_1_N[cpu.PC], &cpu);
    }

    return 0;
}