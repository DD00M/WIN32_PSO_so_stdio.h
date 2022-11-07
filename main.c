#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#include <windows.h>

#include "so_stdio.h"

#define _WIN32

int main(){
    SO_FILE *file = so_fopen("./myOut.txt", "w");
    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    BOOL write = true;
    DWORD bytesWrite;

    //CHAR buffer[10 + 1];
    printf("a intrat aici\n");
    for (int i = 0; i < 8; i++){
        so_fputc('c', file);
    }
    printf("shoalalal:%d\n", file->off_written);
    int k = so_fflush(file);
    printf("%d\n", k);
    return 0;
}