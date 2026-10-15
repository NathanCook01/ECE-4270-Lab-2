#include "Lab2.h"
#include <stdio.h>

void main(int argc, char* argv[]){
    FILE* fp = fopen("sample_asm.txt", "r");
    char buffer[100][100];
    init_buffer(buffer);
    file_to_buffer(fp, buffer);
    print_buffer(buffer);
    // print_char_grid(buffer);
}