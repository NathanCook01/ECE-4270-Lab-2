#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_INS 100
#define MAX_CHAR_PER_LINE 100

// Function to read .txt file that has RV32 and write into a buffer
void file_to_buffer(FILE* fp, char buffer[100][100]);

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
typedef struct UTYPE_INSTRUCTION{ 
    int32_t opcode;     // bits 0 - 6
    int32_t rd;         // bits 7 - 11 
    int32_t imm;        // bits 12 - 31
} u_ins_t;

// struct to hold info for J type instructions
typedef struct JTYPE_INSTRUCTION{ 
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
} j_ins_t;

void file_to_buffer(FILE* fp, char buffer[100][100]){ // assume fp is open for read
    size_t i = 0;
    size_t j = 0;
    char character;
    char throwaway[MAX_CHAR_PER_LINE]; // used to ignore certain things from input (comments & newline)
    while (i < MAX_INS){
        while (j < MAX_CHAR_PER_LINE-1 && (character = fgetc(fp)) != EOF){
            // Ignores lines that start w comments or blank lines
            if((character == '#' || character == '\n') && j == 0){
                // buffer[i][j] = '\n';
                fgets(throwaway, 100, fp);
                break;
            }
            // treats lines ending w comments as newline characters
            else if(character == '#' || character == '\n'){
                buffer[i][j] = '\n';
                fgets(throwaway, 100, fp);
                break;
            }
            // else if(character == '\n' && j == 0){
            //     // buffer[i][j] = '\n';
            //     fgets(throwaway, 100, fp);
            //     break;
            // }

            buffer[i][j] = character;
            j++;
        }
        j=0;
        i++;
    }
}

void print_buffer(char buffer[MAX_INS][MAX_CHAR_PER_LINE]){
    for(int i=0; i < MAX_INS; i++){
        printf("%s", buffer[i]);
    }
}

void init_buffer(char buffer[MAX_CHAR_PER_LINE][MAX_INS]){
    for(int i=0; i < MAX_INS; i++){
        for(int j=0; j< MAX_CHAR_PER_LINE; j++){
            buffer[i][j]=0;
        }
    }
}

