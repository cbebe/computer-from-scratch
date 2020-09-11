#ifndef _ALU_H_
#define _ALU_H_

enum { NO = 0, FN, NY, ZY, NX, ZX, ZR, NG };

enum flags_and_ctrl_bits {
    C_NO = 1 << NO,  // bitwise negate output
    C_FN = 1 << FN,  // 1 for ADD, 0 for bitwise AND
    C_NY = 1 << NY,  // bitwise negate y
    C_ZY = 1 << ZY,  // zero y
    C_NX = 1 << NX,  // bitwise negate x
    C_ZX = 1 << ZX,  // zero x
    F_ZR = 1 << ZR,  // zero flag (res == 0)
    F_NG = 1 << NG   // negative flag (res < 0)
};

// some macros for operations
enum { CZNX = C_NX | C_ZX, CZNY = C_NY | C_ZY, CFNO = C_FN | C_NO };

// 18 notable operations that the ALU can do (there are 64 total)
enum ops {
    OP_C0 = C_ZX | C_ZY | C_FN,  // constant 0
    OP_C1 = CZNX | CZNY | CFNO,  // constant 1
    OP_N1 = CZNX | C_ZY | C_FN,  // constant -1
    OP_CX = CZNY,                // constant x
    OP_CY = CZNX,                // constant y
    OP_FX = CZNY | C_NO,         // bitwise negate (flip) x
    OP_FY = CZNX | C_NO,         // bitwise negate (flip) y
    OP_NX = CZNY | C_FN | C_NO,  // negative x
    OP_NY = CZNX | C_FN | C_NO,  // negative y
    OP_IX = C_NX | CZNY | CFNO,  // increment x (by 1)
    OP_IY = CZNX | C_NY | CFNO,  // increment y (by 1)
    OP_DX = CZNY | C_FN,         // decrement x (by 1)
    OP_DY = CZNX | C_FN,         // decrement y (by 1)
    OP_AD = C_FN,                // add x and y
    OP_SY = C_NX | CFNO,         // subtract y from x
    OP_SX = C_NY | CFNO,         // subtract x from y
    OP_AN = 0,                   // bitwise and (x & y)
    OP_OR = C_NX | C_NY | C_NO   // bitwise or (x | y)
};

#endif