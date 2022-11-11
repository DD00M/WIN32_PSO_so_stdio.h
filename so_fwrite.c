#include <windows.h>
#include <string.h>

#include "so_stdio.h"

#include <stdio.h>

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
    if (strcmp(stream->mode, "r") == 0){
        printf("eroare mode\n");
        stream->isERR = 999;
        return 0;
    }
    if (nmemb <= 0 || size <= 0)
    {
        printf("eroare nmemb size\n");
        stream->isERR = 999;
        return 0; 
    }
    if (stream->read_flag == 1){
        //printf("pe read\n");
        stream->buffer_index = 0;
        stream->read_flag = 0;
    }
    if (stream == NULL)
    {
        printf("is nuLL\n");
        stream->isERR = 999;
        return 0;
    }
    char *aux = (char *)ptr;
    int c = 0;
    int s = 0;
    int i = 0;
    int p = 0;
    int lala = 0;

    while (i < nmemb)
    {
        s = size;
        do
        {
            so_fputc((int)aux[p], stream);
            //printf("%c\n", aux[p]);
            p++;
        }while(--s);
        i++;
    }

    stream->prev = WRITEprev;
    stream->isERR = 888;
    return i;
}