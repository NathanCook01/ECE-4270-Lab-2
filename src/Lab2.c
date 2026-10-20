#include "Lab2.h"

/*
To read in asm into a buffer
    1. create buffer with size MAX_INS by MAX_CHAR_PER_LINE
    2. clear that buffer with clear_buffer()
    3. read in asm text with file_to_buffer
    4. parse instructions into gen_ins_array with create_ins_array()
    5. encode and write 32-bit hex machine code to output file
*/

int main(int argc, char* argv[]){
    if(argc < 2){ // Check for valid argument
        printf("Invalid arguments, try: ./Lab2 <myASM.txt> [output.txt]\n");
        return -1;
    }
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Could not open that file. Goodbye\n");
        return -1;
    }

    const char* out_filename = (argc >= 3) ? argv[2] : "output.txt";
    FILE *out_fp = fopen(out_filename, "w");
    if(out_fp == NULL){
        printf("Could not open output file %s.\n", out_filename);
        fclose(fp);
        return -1;
    }

    char buffer[MAX_INS][MAX_CHAR_PER_LINE];
    gen_ins_t gen_ins_array[MAX_INS];

    clear_buffer(buffer);
    file_to_buffer(fp, buffer);
    fclose(fp);

    int ins_count = create_ins_array(gen_ins_array, buffer);
    write_machine_code(out_fp, gen_ins_array, ins_count);
    fclose(out_fp);

    printf("Successfully assembled %d instructions to %s\n", ins_count, out_filename);
    return 0;
}