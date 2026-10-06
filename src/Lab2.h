#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

// struct to hold info for R type instructions
typedef struct RTYPE_INSTRUCTION{ 
    int32_t opcode;     // bits 0 - 6
    int32_t rd;         // bits 7 - 11
    int32_t f3;         // bits 12 - 14
    int32_t rs1;        // bits 15 - 19
    int32_t rs2;        // bits 20 - 24
    int32_t f7;         // bits 25 - 31
} r_ins_t;

// struct to hold info for I type instructions
typedef struct ITYPE_INSTRUCTION{ 
    int32_t opcode;     // bits 0 - 6
    int32_t rd;         // bits 7 - 11
    int32_t f3;         // bits 12 - 14
    int32_t rs1;        // bits 15 - 19
    int32_t imm;        // bits 20 - 31
} i_ins_t;

// struct to hold info for S type instructions
typedef struct STYPE_INSTRUCTION{ 
    int32_t opcode;     // bits 0 - 6
    int32_t imm1;       // bits 7 - 11
    int32_t f3;         // bits 12 - 14
    int32_t rs1;        // bits 15 - 19
    int32_t rs2;        // bits 20 - 24
    int32_t imm2;       // bits 25 - 31
} s_ins_t;

// struct to hold info for B type instructions
typedef struct BTYPE_INSTRUCTION{ 
    int32_t opcode;     // bits 0 - 6
    int32_t imm1;       // bits 7 - 11 README instruction bit 7 holds the 11th bit of the immediate
    int32_t f3;         // bits 12 - 14
    int32_t rs1;        // bits 15 - 19
    int32_t rs2;        // bits 20 - 24
    int32_t imm2;       // bits 25 - 31 README instruction bit 31 holds the 12th bit of the immediate
} b_ins_t;

// struct to hold info for U type instructions
typedef struct BTYPE_INSTRUCTION{ 
    int32_t opcode;     // bits 0 - 6
    int32_t rd;         // bits 7 - 11 
    int32_t imm;        // bits 12 - 31
} b_ins_t;

// struct to hold info for J type instructions
typedef struct BTYPE_INSTRUCTION{ 
    int32_t opcode;     // bits 0 - 6
    int32_t rd;         // bits 7 - 11 
    int32_t imm;        // bits 12 - 31
    /*  README
        immediate formatting
        instruction bits 12 - 19 hold immediate bits 12 - 19
        instruction bit 20 holds the 11th immediate bit
        instruction bits 21-30 bit immediate bits 1 - 10
        instruction bit 31 holds the 20th immediate bit
    */
} b_ins_t;