#include <windows.h>
#include <string.h>
#include "so_stdio.h"
#include <stdio.h>

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream){
    if (strcmp(stream->mode, "w") == 0){
        return SO_EOF;
    }  
    if (stream->is_file != 1){
        return SO_EOF;
    }
    if (strcmp(stream->mode, "a") == 0){
        stream->cursor = (unsigned int)SetFilePointer(stream->so_handle, 0, NULL, FILE_END);
    }
    
    if (strcmp(stream->mode, "a+") == 0){
        //SetFilePointer(stream->so_handle, 0, NULL, FILE_END);
    }

    if (nmemb <= 0 || size <= 0){
        return SO_EOF;
    }
    if (stream == NULL){
        return SO_EOF;
    }
    char *aux = ptr;
    int c = 0;
    int s = 0;
    int i = 0;
    int p = 0;
    int lala = 0;
    if (size*nmemb >= stream->so_sizeFile){
       lala = stream->so_sizeFile;
    }else {lala = size * nmemb; }
    //printf("salut\n");
    while (i < lala)
    {
            c = so_fgetc(stream);
            //printf("%c\n", c);
            if (stream->eof || stream->flagERR == -1){
                return i / size;
            }
            //printf("%c\n", c);
            aux[p] = (char)c;
            p++;
        i++;
    }
    stream->read_flag = 1;
    stream->prev = READprev;

    return i / size;
}