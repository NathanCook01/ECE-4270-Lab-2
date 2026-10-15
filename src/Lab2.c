#include "Lab2.h"

/*
To read in asm into a buffer
    1. create buffer with size MAX_INS by MAX_CHAR_PER_LINE
    2. clear that buffer with clear_buffer()
    3. read in asm text with file_to_buffer
*/

int main(int argc, char* argv[]){
    if(argc < 2){ // Check for valid argument
        printf("Invalid arguments, try: ./Lab2 <myASM.txt>\n");
        return -1;
    }
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Could not open that file. Goodbye\n");
        return -1;
    }

    char buffer[MAX_INS][MAX_CHAR_PER_LINE];
    clear_buffer(buffer);
    file_to_buffer(fp, buffer);
    print_buffer(buffer);
    return 0;
}