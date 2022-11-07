#include <windows.h>
#include <string.h>

#include "so_stdio.h"

#include <stdio.h>

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
    if (strcmp(stream->mode, "r") == 0){
        return SO_EOF;
    }
    if (nmemb <= 0 || size <= 0)
    {
        return 0; 
    }
    else
    {
        if (stream->read_flag == 1){
            stream->buffer_index = 0;
            stream->read_flag = 0;
        }
        if (stream == NULL)
        {
            return 0;
        }
        else
        {
            char *aux = (char *)ptr;
            int t = 0;
            int i = 0;
            for (int j = 0; j < nmemb; j++)
            {
                for (int i = t; i < size; i++)
                {
                    if(stream->buffer_index == BUFSIZE){
                        i--;
                    }
                    so_fputc((int)aux[i], stream);
                }
                t = i;
            }
            stream->prev = WRITEprev;
            return size * nmemb;
        }
    }
}