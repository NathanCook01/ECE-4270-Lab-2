#define _GNU_SOURCE
// #include "Lab2.h"
#include <string.h>
#include <stdio.h>

void main(int argc, char* argv[]){
    // FILE* fp = fopen("sample_asm.txt", "r");
    // char buffer[100][100];
    // clear_buffer(buffer);
    // file_to_buffer(fp, buffer);
    // print_buffer(buffer);
    // // print_char_grid(buffer)
    char str[] = "Hello, World! This is C.";
    char *token;

    // First call: specify the string
    token = strtok(str, ", !.");
    while (token != NULL) {
        printf("Token: %s\n", token);
        // Subsequent calls: use NULL
        token = strtok(NULL, ", !.");
    }
}