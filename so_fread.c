#include <windows.h>
#include <string.h>
#include "so_stdio.h"

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream){
    if (strcmp(stream->mode, "w") == 0){
        return SO_EOF;
    }    
    if (nmemb <= 0 || size <= 0){
        return 0;
    }else{
        if (stream == NULL){
            return 0;
        }else{
            int t = 0;
            int i = 0;
            char *aux = (char*)ptr;
            for (int j = 0; j < nmemb; j++){
                for (i = t; i < size; i++){
                    int k = so_fgetc(stream);
                    aux[i] = (char)k;
                }
                t = i;
            }
            stream->read_flag = 1;
            stream->prev = READprev;
            return size*nmemb;
        }
    }
}