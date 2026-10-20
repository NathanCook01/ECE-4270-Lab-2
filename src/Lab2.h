#ifndef LAB2_H // include guard
#define LAB2_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_INS 100
#define MAX_CHAR_PER_LINE 100

// Function to read .txt file that has RV32 and write into a buffer
void file_to_buffer(FILE* fp, char buffer[MAX_INS][MAX_CHAR_PER_LINE]);
// void create_ins_array(gen_ins_t gen_ins_array[MAX_INS], char buffer[MAX_INS][MAX_CHAR_PER_LINE]);

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


// once the buffer is populated, use an array of this struct to organize
// makes things easier later
typedef struct GENERAL_INSTRUCTION{
    int type_flag;
    /*
    1->r
    2->i
    3->s
    4->b
    5->u
    6->j
    */
    char label[16];
    r_ins_t r_type;
    i_ins_t i_type;
    s_ins_t s_type;
    b_ins_t b_type;
    u_ins_t u_type;
    j_ins_t j_type;
}gen_ins_t;

typedef struct LABEL_ENTRY{
    char name[16];
    int ins_index;
} label_entry_t;

// remove whitespace from a buffer line
char* trim_whitespace(char* s){
    if (!s) return NULL;
    while(isspace(*s)) s++; // trim leading whitespace
    if(*s == 0) return s;

    char* end = s + strlen(s) - 1;
    
    while (end > s && isspace((unsigned char)*end)) { // trim trailing whitespace
        *end = '\0';
        end--;
    }

    return s;
}

int32_t parse_register(char* reg_str){
    if(!reg_str) return 0;
    while(isspace((unsigned char)*reg_str)) reg_str++;

    if (reg_str[0] == 'x' || reg_str[0] == 'X') {
        return (int32_t)strtol(reg_str + 1, NULL, 10);
    }
    if (strcmp(reg_str, "zero") == 0 || strcmp(reg_str, "0") == 0) return 0;
    if (strcmp(reg_str, "ra") == 0) return 1;
    if (strcmp(reg_str, "sp") == 0) return 2;
    if (strcmp(reg_str, "gp") == 0) return 3;
    if (strcmp(reg_str, "tp") == 0) return 4;
    if (strcmp(reg_str, "t0") == 0) return 5;
    if (strcmp(reg_str, "t1") == 0) return 6;
    if (strcmp(reg_str, "t2") == 0) return 7;
    if (strcmp(reg_str, "s0") == 0 || strcmp(reg_str, "fp") == 0) return 8;
    if (strcmp(reg_str, "s1") == 0) return 9;
    if (strcmp(reg_str, "a0") == 0) return 10;
    if (strcmp(reg_str, "a1") == 0) return 11;
    if (strcmp(reg_str, "a2") == 0) return 12;
    if (strcmp(reg_str, "a3") == 0) return 13;
    if (strcmp(reg_str, "a4") == 0) return 14;
    if (strcmp(reg_str, "a5") == 0) return 15;
    if (strcmp(reg_str, "a6") == 0) return 16;
    if (strcmp(reg_str, "a7") == 0) return 17;
    if (strcmp(reg_str, "s2") == 0) return 18;
    if (strcmp(reg_str, "s3") == 0) return 19;
    if (strcmp(reg_str, "s4") == 0) return 20;
    if (strcmp(reg_str, "s5") == 0) return 21;
    if (strcmp(reg_str, "s6") == 0) return 22;
    if (strcmp(reg_str, "s7") == 0) return 23;
    if (strcmp(reg_str, "s8") == 0) return 24;
    if (strcmp(reg_str, "s9") == 0) return 25;
    if (strcmp(reg_str, "s10") == 0) return 26;
    if (strcmp(reg_str, "s11") == 0) return 27;
    if (strcmp(reg_str, "t3") == 0) return 28;
    if (strcmp(reg_str, "t4") == 0) return 29;
    if (strcmp(reg_str, "t5") == 0) return 30;
    if (strcmp(reg_str, "t6") == 0) return 31;

    return 0;
}

int find_label_index(label_entry_t labels[], int label_count, const char* name){
    char clean_name[16];
    snprintf(clean_name, sizeof(clean_name), "%s", name);
    // Strip any trailing colon in label references (e.g., "exit:" in "bge x11, x12, exit:")
    size_t len = strlen(clean_name);
    if (len > 0 && clean_name[len - 1] == ':') {
        clean_name[len - 1] = '\0';
    }
    for (int i = 0; i < label_count; i++) {
        if (strcmp(labels[i].name, clean_name) == 0) {
            return labels[i].ins_index;
        }
    }
    return -1;
}

// copy input from file into a buffer, trims comments and blank lines
void file_to_buffer(FILE* fp, char buffer[MAX_INS][MAX_CHAR_PER_LINE]){ // assume fp is open for read
    size_t i = 0;
    size_t j = 0;
    char character;
    char throwaway[MAX_CHAR_PER_LINE]; // used to ignore certain things from input (comments & newline)
    while (i < MAX_INS){
        j=0;
        int eof_flag=0;
        while (j < (MAX_CHAR_PER_LINE - 1)){
            character = fgetc(fp);
            if (character == EOF){
                eof_flag = 1;
                break; 
            }

            // Ignore leading whitespace
            if ((character == ' ' || character == '\t' || character == '\r') && j == 0) {
                continue;
            }

            // Ignore lines that start with a comment
            if (character == '#' && j == 0) {
                if (fgets(throwaway, MAX_CHAR_PER_LINE, fp) == NULL) eof_flag = 1;                
                break;
            }

            // Ignore blank lines
            else if (character == '\n' && j == 0) {
                break;
            }

            // Inline comment: terminate line with '\n' and flush the rest of the comment
            else if (character == '#') {
                buffer[i][j++] = '\n';
                buffer[i][j] = '\0';
                if (fgets(throwaway, MAX_CHAR_PER_LINE, fp) == NULL) eof_flag = 1;                
                break;
            }

            // Normal end of line: store '\n' and stop reading this line
            else if (character == '\n') {
                buffer[i][j++] = '\n';
                buffer[i][j] = '\0';
                break;
            }
            if (character != '\r') {
                buffer[i][j++] = character;
            }
        }
        if(j > 0){
            if(buffer[i][j-1] != '\n' && j< (MAX_CHAR_PER_LINE-1)){
                buffer[i][j++] = '\n';
            }
            buffer[i][j] = '\0';
            i++;
        }
        if(eof_flag) break;
    }
}

// displays the buffer (used for testing)
void print_buffer(char buffer[MAX_INS][MAX_CHAR_PER_LINE]){
    for(int i=0; i < MAX_INS; i++){
        if(buffer[i][0] != '\0'){        
            printf("%s", buffer[i]);
        }
    }
}

// clears the buffer (used for testing, replaced later with memset)
void clear_buffer(char buffer[MAX_CHAR_PER_LINE][MAX_INS]){
    for(int i=0; i < MAX_INS; i++){
        for(int j=0; j< MAX_CHAR_PER_LINE; j++){
            buffer[i][j]=0;
        }
    }
}

// Creates an array of general instruction structs from the buffer
int create_ins_array(gen_ins_t gen_ins_array[MAX_INS], char buffer[MAX_INS][MAX_CHAR_PER_LINE]){
    memset(gen_ins_array, 0, sizeof(gen_ins_t) * MAX_INS);
    label_entry_t labels[MAX_INS];
    int label_count = 0;

    char clean_ins_lines[MAX_INS][MAX_CHAR_PER_LINE];
    memset(clean_ins_lines, 0, sizeof(clean_ins_lines));
    int ins_count = 0;

    // First pass through the buffer will clear labels & align instructions
    for(int i=0; i<MAX_INS && buffer[i][0] != '\0'; i++){
        char line_copy[MAX_CHAR_PER_LINE];
        snprintf(line_copy, sizeof(line_copy), "%s", buffer[i]);
        char* line = trim_whitespace(line_copy);
        if (*line == '\0') continue;

        char* colon = strchr(line, ':');
        // Need to make sure the colon is actually a label and not an immediate
        if(colon){
            char* first_space = strpbrk(line, " \t,");
            if(!first_space || colon < first_space){
                *colon = '\0';
                char* label_name = trim_whitespace(line);
                if(label_count < MAX_INS){
                    snprintf(labels[label_count].name, 16, "%s", label_name);
                    labels[label_count].ins_index = ins_count;
                    label_count++;
                }
                if (ins_count < MAX_INS) {
                    snprintf(gen_ins_array[ins_count].label, 16, "%s", label_name);
                }
                // Check if there is an instruction on the same line after the colon
                char* remainder = trim_whitespace(colon + 1);
                if (*remainder != '\0') {
                    snprintf(clean_ins_lines[ins_count], MAX_CHAR_PER_LINE, "%s", remainder);
                    ins_count++;
                }
                continue;
            }
        }

        snprintf(clean_ins_lines[ins_count], MAX_CHAR_PER_LINE, "%s", line);
        ins_count++;
    }

    // Second pass through will convert each buffer line into a gen_ins_t object
    for(int i=0; i< ins_count; i++){
        char line[MAX_CHAR_PER_LINE];
        strncpy(line, clean_ins_lines[i], sizeof(line) - 1);
        line[sizeof(line) - 1] = '\0';        char* mnemonic = strtok(line, " \t,\n");
        if(!mnemonic) continue;

        char* op1 = strtok(NULL, " \t,\n");
        char* op2 = strtok(NULL, " \t,\n");
        char* op3 = strtok(NULL, " \t,\n");

        // Handle PDF syntax where "sll rd, rs1, imm" is written with an immediate shift amount
        int is_shift_imm = 0;
        if ((strcmp(mnemonic, "sll") == 0 || strcmp(mnemonic, "srl") == 0 || strcmp(mnemonic, "sra") == 0) && op3 != NULL) {
            if (isdigit((unsigned char)op3[0]) || op3[0] == '-') {
                is_shift_imm = 1;
            }
        }

        // R types
        if (!is_shift_imm &&(
            strcmp(mnemonic, "add") == 0  || strcmp(mnemonic, "sub") == 0  ||
            strcmp(mnemonic, "sll") == 0  || strcmp(mnemonic, "slt") == 0  ||
            strcmp(mnemonic, "sltu") == 0 || strcmp(mnemonic, "xor") == 0  ||
            strcmp(mnemonic, "srl") == 0  || strcmp(mnemonic, "sra") == 0  ||
            strcmp(mnemonic, "or") == 0   || strcmp(mnemonic, "and") == 0  ||
            strcmp(mnemonic, "mul") == 0)){

            gen_ins_array[i].type_flag = 1;
            gen_ins_array[i].r_type.opcode = 0x33;
            gen_ins_array[i].r_type.rd  = parse_register(op1);
            gen_ins_array[i].r_type.rs1 = parse_register(op2);
            gen_ins_array[i].r_type.rs2 = parse_register(op3);
            gen_ins_array[i].r_type.f7  = 0x00;

            if (strcmp(mnemonic, "add") == 0) {
                gen_ins_array[i].r_type.f3 = 0x0;
            } else if (strcmp(mnemonic, "sub") == 0) {
                gen_ins_array[i].r_type.f3 = 0x0;
                gen_ins_array[i].r_type.f7 = 0x20;
            } else if (strcmp(mnemonic, "sll") == 0) {
                gen_ins_array[i].r_type.f3 = 0x1;
            } else if (strcmp(mnemonic, "slt") == 0) {
                gen_ins_array[i].r_type.f3 = 0x2;
            } else if (strcmp(mnemonic, "sltu") == 0) {
                gen_ins_array[i].r_type.f3 = 0x3;
            } else if (strcmp(mnemonic, "xor") == 0) {
                gen_ins_array[i].r_type.f3 = 0x4;
            } else if (strcmp(mnemonic, "srl") == 0) {
                gen_ins_array[i].r_type.f3 = 0x5;
            } else if (strcmp(mnemonic, "sra") == 0) {
                gen_ins_array[i].r_type.f3 = 0x5;
                gen_ins_array[i].r_type.f7 = 0x20;
            } else if (strcmp(mnemonic, "or") == 0) {
                gen_ins_array[i].r_type.f3 = 0x6;
            } else if (strcmp(mnemonic, "and") == 0) {
                gen_ins_array[i].r_type.f3 = 0x7;
            } else if (strcmp(mnemonic, "mul") == 0) {
                gen_ins_array[i].r_type.f3 = 0x0;
                gen_ins_array[i].r_type.f7 = 0x01;
            }
        }
        // I Types
        else if (is_shift_imm ||
            strcmp(mnemonic, "addi") == 0  || strcmp(mnemonic, "slti") == 0  ||
            strcmp(mnemonic, "sltiu") == 0 || strcmp(mnemonic, "xori") == 0  ||
            strcmp(mnemonic, "ori") == 0   || strcmp(mnemonic, "andi") == 0  ||
            strcmp(mnemonic, "slli") == 0  || strcmp(mnemonic, "srli") == 0  ||
            strcmp(mnemonic, "srai") == 0  || strcmp(mnemonic, "lw") == 0    ||
            strcmp(mnemonic, "lh") == 0    || strcmp(mnemonic, "lb") == 0    ||
            strcmp(mnemonic, "lhu") == 0   || strcmp(mnemonic, "lbu") == 0   ||
            strcmp(mnemonic, "jalr") == 0  || strcmp(mnemonic, "li") == 0    ||
            strcmp(mnemonic, "mv") == 0    || strcmp(mnemonic, "nop") == 0   ||
            strcmp(mnemonic, "ret") == 0   || strcmp(mnemonic, "jr") == 0) {

            gen_ins_array[i].type_flag = 2;

            if (strcmp(mnemonic, "nop") == 0) {
                gen_ins_array[i].i_type.opcode = 0x13;
                gen_ins_array[i].i_type.rd  = 0;
                gen_ins_array[i].i_type.f3  = 0;
                gen_ins_array[i].i_type.rs1 = 0;
                gen_ins_array[i].i_type.imm = 0;
            } else if (strcmp(mnemonic, "li") == 0) { // Pseudo: addi rd, x0, imm
                gen_ins_array[i].i_type.opcode = 0x13;
                gen_ins_array[i].i_type.rd  = parse_register(op1);
                gen_ins_array[i].i_type.f3  = 0x0;
                gen_ins_array[i].i_type.rs1 = 0;
                gen_ins_array[i].i_type.imm = (int32_t)strtol(op2, NULL, 0);
            } else if (strcmp(mnemonic, "mv") == 0) { // Pseudo: addi rd, rs1, 0
                gen_ins_array[i].i_type.opcode = 0x13;
                gen_ins_array[i].i_type.rd  = parse_register(op1);
                gen_ins_array[i].i_type.f3  = 0x0;
                gen_ins_array[i].i_type.rs1 = parse_register(op2);
                gen_ins_array[i].i_type.imm = 0;
            } else if (strcmp(mnemonic, "ret") == 0) { // Pseudo: jalr x0, x1, 0
                gen_ins_array[i].i_type.opcode = 0x67;
                gen_ins_array[i].i_type.rd  = 0;
                gen_ins_array[i].i_type.f3  = 0x0;
                gen_ins_array[i].i_type.rs1 = 1;
                gen_ins_array[i].i_type.imm = 0;
            } else if (strcmp(mnemonic, "jr") == 0) { // Pseudo: jalr x0, rs1, 0
                gen_ins_array[i].i_type.opcode = 0x67;
                gen_ins_array[i].i_type.rd  = 0;
                gen_ins_array[i].i_type.f3  = 0x0;
                gen_ins_array[i].i_type.rs1 = parse_register(op1);
                gen_ins_array[i].i_type.imm = 0;
            } else if (strcmp(mnemonic, "lw") == 0 || strcmp(mnemonic, "lh") == 0 ||
                       strcmp(mnemonic, "lb") == 0 || strcmp(mnemonic, "lhu") == 0 ||
                       strcmp(mnemonic, "lbu") == 0) {
                // Format: lw rd, offset(rs1)
                gen_ins_array[i].i_type.opcode = 0x03;
                gen_ins_array[i].i_type.rd = parse_register(op1);
                if (strcmp(mnemonic, "lb") == 0)       gen_ins_array[i].i_type.f3 = 0x0;
                else if (strcmp(mnemonic, "lh") == 0)  gen_ins_array[i].i_type.f3 = 0x1;
                else if (strcmp(mnemonic, "lw") == 0)  gen_ins_array[i].i_type.f3 = 0x2;
                else if (strcmp(mnemonic, "lbu") == 0) gen_ins_array[i].i_type.f3 = 0x4;
                else if (strcmp(mnemonic, "lhu") == 0) gen_ins_array[i].i_type.f3 = 0x5;

                char* l_paren = strchr(op2, '(');
                if (l_paren) {
                    *l_paren = '\0';
                    char* r_paren = strchr(l_paren + 1, ')');
                    if (r_paren) *r_paren = '\0';
                    gen_ins_array[i].i_type.imm = (int32_t)strtol(op2, NULL, 0);
                    gen_ins_array[i].i_type.rs1 = parse_register(l_paren + 1);
                } else {
                    gen_ins_array[i].i_type.rs1 = parse_register(op2);
                    gen_ins_array[i].i_type.imm = op3 ? (int32_t)strtol(op3, NULL, 0) : 0;
                }
            } else if (strcmp(mnemonic, "jalr") == 0) {
                gen_ins_array[i].i_type.opcode = 0x67;
                gen_ins_array[i].i_type.f3 = 0x0;
                gen_ins_array[i].i_type.rd = parse_register(op1);
                char* l_paren = op2 ? strchr(op2, '(') : NULL;
                if (l_paren) {
                    *l_paren = '\0';
                    char* r_paren = strchr(l_paren + 1, ')');
                    if (r_paren) *r_paren = '\0';
                    gen_ins_array[i].i_type.imm = (int32_t)strtol(op2, NULL, 0);
                    gen_ins_array[i].i_type.rs1 = parse_register(l_paren + 1);
                } else {
                    gen_ins_array[i].i_type.rs1 = parse_register(op2);
                    gen_ins_array[i].i_type.imm = op3 ? (int32_t)strtol(op3, NULL, 0) : 0;
                }
            } else {
                // Arithmetic/Logical I-type (addi, slli, etc.)
                gen_ins_array[i].i_type.opcode = 0x13;
                gen_ins_array[i].i_type.rd  = parse_register(op1);
                gen_ins_array[i].i_type.rs1 = parse_register(op2);
                int32_t imm_val = (int32_t)strtol(op3, NULL, 0);

                if (strcmp(mnemonic, "addi") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x0;
                    gen_ins_array[i].i_type.imm = imm_val;
                } else if (strcmp(mnemonic, "slli") == 0 || strcmp(mnemonic, "sll") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x1;
                    gen_ins_array[i].i_type.imm = imm_val & 0x1F;
                } else if (strcmp(mnemonic, "slti") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x2;
                    gen_ins_array[i].i_type.imm = imm_val;
                } else if (strcmp(mnemonic, "sltiu") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x3;
                    gen_ins_array[i].i_type.imm = imm_val;
                } else if (strcmp(mnemonic, "xori") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x4;
                    gen_ins_array[i].i_type.imm = imm_val;
                } else if (strcmp(mnemonic, "srli") == 0 || strcmp(mnemonic, "srl") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x5;
                    gen_ins_array[i].i_type.imm = imm_val & 0x1F;
                } else if (strcmp(mnemonic, "srai") == 0 || strcmp(mnemonic, "sra") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x5;
                    gen_ins_array[i].i_type.imm = (0x20 << 5) | (imm_val & 0x1F);
                } else if (strcmp(mnemonic, "ori") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x6;
                    gen_ins_array[i].i_type.imm = imm_val;
                } else if (strcmp(mnemonic, "andi") == 0) {
                    gen_ins_array[i].i_type.f3  = 0x7;
                    gen_ins_array[i].i_type.imm = imm_val;
                }
            }
        }
        // S Types
        else if (strcmp(mnemonic, "sw") == 0 || strcmp(mnemonic, "sh") == 0 || strcmp(mnemonic, "sb") == 0) {
            // Format: sw rs2, offset(rs1)
            gen_ins_array[i].type_flag = 3;
            gen_ins_array[i].s_type.opcode = 0x23;
            gen_ins_array[i].s_type.rs2 = parse_register(op1);

            if (strcmp(mnemonic, "sb") == 0)      gen_ins_array[i].s_type.f3 = 0x0;
            else if (strcmp(mnemonic, "sh") == 0) gen_ins_array[i].s_type.f3 = 0x1;
            else if (strcmp(mnemonic, "sw") == 0) gen_ins_array[i].s_type.f3 = 0x2;

            int32_t offset = 0;
            char* l_paren = strchr(op2, '(');
            if (l_paren) {
                *l_paren = '\0';
                char* r_paren = strchr(l_paren + 1, ')');
                if (r_paren) *r_paren = '\0';
                offset = (int32_t)strtol(op2, NULL, 0);
                gen_ins_array[i].s_type.rs1 = parse_register(l_paren + 1);
            }
            // imm1 (bits 7-11) = offset[4:0], imm2 (bits 25-31) = offset[11:5]
            gen_ins_array[i].s_type.imm1 = offset & 0x1F;
            gen_ins_array[i].s_type.imm2 = (offset >> 5) & 0x7F;
        }
        // B types
        else if (strcmp(mnemonic, "beq") == 0  || strcmp(mnemonic, "bne") == 0  ||
                 strcmp(mnemonic, "blt") == 0  || strcmp(mnemonic, "bge") == 0  ||
                 strcmp(mnemonic, "bltu") == 0 || strcmp(mnemonic, "bgeu") == 0 ||
                 strcmp(mnemonic, "bgt") == 0  || strcmp(mnemonic, "ble") == 0) {

            gen_ins_array[i].type_flag = 4;
            gen_ins_array[i].b_type.opcode = 0x63;

            // Support pseudo-branches bgt / ble by swapping rs1 and rs2
            if (strcmp(mnemonic, "bgt") == 0) {
                gen_ins_array[i].b_type.f3  = 0x4; // blt rs2, rs1, label
                gen_ins_array[i].b_type.rs1 = parse_register(op2);
                gen_ins_array[i].b_type.rs2 = parse_register(op1);
            } else if (strcmp(mnemonic, "ble") == 0) {
                gen_ins_array[i].b_type.f3  = 0x5; // bge rs2, rs1, label
                gen_ins_array[i].b_type.rs1 = parse_register(op2);
                gen_ins_array[i].b_type.rs2 = parse_register(op1);
            } else {
                gen_ins_array[i].b_type.rs1 = parse_register(op1);
                gen_ins_array[i].b_type.rs2 = parse_register(op2);
                if (strcmp(mnemonic, "beq") == 0)       gen_ins_array[i].b_type.f3 = 0x0;
                else if (strcmp(mnemonic, "bne") == 0)  gen_ins_array[i].b_type.f3 = 0x1;
                else if (strcmp(mnemonic, "blt") == 0)  gen_ins_array[i].b_type.f3 = 0x4;
                else if (strcmp(mnemonic, "bge") == 0)  gen_ins_array[i].b_type.f3 = 0x5;
                else if (strcmp(mnemonic, "bltu") == 0) gen_ins_array[i].b_type.f3 = 0x6;
                else if (strcmp(mnemonic, "bgeu") == 0) gen_ins_array[i].b_type.f3 = 0x7;
            }

            int32_t offset = 0;
            int target_idx = find_label_index(labels, label_count, op3);
            if (target_idx != -1) {
                offset = (target_idx - i) * 4;
            } else {
                offset = (int32_t)strtol(op3, NULL, 0);
            }

            // Per Lab2.h README:
            // imm1 (bits 7-11): bit 7 holds imm[11], bits 8-11 hold imm[4:1]
            // imm2 (bits 25-31): bits 25-30 hold imm[10:5], bit 31 holds imm[12]
            gen_ins_array[i].b_type.imm1 = (((offset >> 4) & 0xFE) | ((offset >> 11) & 0x01)) & 0x1F;
            gen_ins_array[i].b_type.imm1 = (((offset >> 1) & 0x0F) << 1) | ((offset >> 11) & 0x01);
            gen_ins_array[i].b_type.imm2 = (((offset >> 12) & 0x01) << 6) | ((offset >> 5) & 0x3F);
        }
        // U Types
        else if (strcmp(mnemonic, "lui") == 0 || strcmp(mnemonic, "auipc") == 0) {
            gen_ins_array[i].type_flag = 5;
            gen_ins_array[i].u_type.opcode = (strcmp(mnemonic, "lui") == 0) ? 0x37 : 0x17;
            gen_ins_array[i].u_type.rd  = parse_register(op1);
            gen_ins_array[i].u_type.imm = (int32_t)strtol(op2, NULL, 0) & 0xFFFFF;
        }
        // J Types
        else if (strcmp(mnemonic, "jal") == 0 || strcmp(mnemonic, "j") == 0) {
            gen_ins_array[i].type_flag = 6;
            gen_ins_array[i].j_type.opcode = 0x6F;

            const char* target_str = NULL;
            if (strcmp(mnemonic, "j") == 0) {
                // Pseudo-instruction: j label -> jal x0, label
                gen_ins_array[i].j_type.rd = 0;
                target_str = op1;
            } else if (op2 == NULL) {
                // jal label -> jal x1, label
                gen_ins_array[i].j_type.rd = 1;
                target_str = op1;
            } else {
                // jal rd, label
                gen_ins_array[i].j_type.rd = parse_register(op1);
                target_str = op2;
            }

            int32_t offset = 0;
            int target_idx = find_label_index(labels, label_count, target_str);
            if (target_idx != -1) {
                offset = (target_idx - i) * 4;
            } else {
                offset = (int32_t)strtol(target_str, NULL, 0);
            }

            // Per Lab2.h README:
            // instruction bits 12-19 hold imm[19:12]
            // instruction bit 20 holds imm[11]
            // instruction bits 21-30 hold imm[10:1]
            // instruction bit 31 holds imm[20]
            int32_t imm20    = (offset >> 20) & 0x1;
            int32_t imm10_1  = (offset >> 1)  & 0x3FF;
            int32_t imm11    = (offset >> 11) & 0x1;
            int32_t imm19_12 = (offset >> 12) & 0xFF;

            gen_ins_array[i].j_type.imm = (imm20 << 19) | (imm10_1 << 9) | (imm11 << 8) | imm19_12;
        }
    }

    return ins_count;
}

// use bitwise operations to convert a general instruction in a 32 bit word
uint32_t encode_instruction(gen_ins_t* ins){
    uint32_t word=0;
    switch(ins->type_flag){
        case 1: // R-type
            word |= (uint32_t)(ins->r_type.opcode & 0x7f);
            word |= (((uint32_t)(ins->r_type.rd & 0x1F)) << 7);
            word |= (((uint32_t)(ins->r_type.f3 & 0x07)) << 12);
            word |= (((uint32_t)(ins->r_type.rs1 & 0x1F)) << 15);
            word |= (((uint32_t)(ins->r_type.rs2 & 0x1F)) << 20);
            word |= (((uint32_t)(ins->r_type.f7 & 0x7F)) << 25);
            break;
        case 2: // I-type
            word |= (uint32_t)(ins->i_type.opcode & 0x7F);
            word |= (uint32_t)(ins->i_type.rd     & 0x1F) << 7;
            word |= (uint32_t)(ins->i_type.f3     & 0x07) << 12;
            word |= (uint32_t)(ins->i_type.rs1    & 0x1F) << 15;
            word |= (uint32_t)(ins->i_type.imm    & 0xFFF) << 20;
            break;
            break;
        case 3: // S-type
            word |= (uint32_t)(ins->s_type.opcode & 0x7F);
            word |= (uint32_t)(ins->s_type.imm1   & 0x1F) << 7;
            word |= (uint32_t)(ins->s_type.f3     & 0x07) << 12;
            word |= (uint32_t)(ins->s_type.rs1    & 0x1F) << 15;
            word |= (uint32_t)(ins->s_type.rs2    & 0x1F) << 20;
            word |= (uint32_t)(ins->s_type.imm2   & 0x7F) << 25;
            break;
        case 4: // B-type
            word |= (uint32_t)(ins->b_type.opcode & 0x7F);
            word |= (uint32_t)(ins->b_type.imm1   & 0x1F) << 7;
            word |= (uint32_t)(ins->b_type.f3     & 0x07) << 12;
            word |= (uint32_t)(ins->b_type.rs1    & 0x1F) << 15;
            word |= (uint32_t)(ins->b_type.rs2    & 0x1F) << 20;
            word |= (uint32_t)(ins->b_type.imm2   & 0x7F) << 25;
            break;
        case 5: // U-type
            word |= (uint32_t)(ins->u_type.opcode & 0x7F);
            word |= (uint32_t)(ins->u_type.rd     & 0x1F) << 7;
            word |= (uint32_t)(ins->u_type.imm    & 0xFFFFF) << 12;
            break;
        case 6: // J-type
            word |= (uint32_t)(ins->j_type.opcode & 0x7F);
            word |= (uint32_t)(ins->j_type.rd     & 0x1F) << 7;
            word |= (uint32_t)(ins->j_type.imm    & 0xFFFFF) << 12;
            break;
        default:
            break;
        
    }
    return word;
}

// FINAL STEP: write all instructions into the output file
void write_machine_code(FILE* out_fp, gen_ins_t gen_ins_array[MAX_INS], int ins_count){
    for(int i=0; i<ins_count; i++){
        uint32_t word = encode_instruction(&gen_ins_array[i]);
        fprintf(out_fp, "%08x\n", word);
    }
}

#endif // include guard