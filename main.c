#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#include <windows.h>

#include "so_stdio.h"

#define _WIN32

int main(){
    SO_FILE *p = so_popen("dir", "r");
    if (p == NULL){
        printf("p is null\n");
        return -1;
    }else{
        printf("here\n");
        char *buffer = (char *)malloc(100*sizeof(char));
        if(buffer = NULL){
            printf("eroare la buffer\n");
            return -1;
        }else{
            printf("intrat pe else\n");
            so_fread(buffer, 20, 1, p);
            printf("%s\n", buffer);
        }
    }
    return 0;
}