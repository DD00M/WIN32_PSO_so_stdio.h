#include <windows.h>
#include <string.h>

#include "so_stdio.h"

#include <stdio.h>

int so_fputc(int c, SO_FILE *stream)
{
    if (strcmp(stream->mode, "r") == 0){
        return SO_EOF;
    }
    if (strcmp(stream->mode, "a") == 0 || strcmp(stream->mode, "a+") == 0){
        SetFilePointer(stream->so_handle, 0, NULL, FILE_END);
    }
    if (stream->prev == READprev){
        stream->buffer_index = 0;
        stream->off_written = 0;
        memset(stream->buffer, 0, BUFSIZE);
    }

    stream->prev = WRITEprev;
    //printf("%d-%d\n", stream->off_written, BUFSIZE);
    if (stream->off_written == BUFSIZE){
        //printf("flas\n");
        so_fflush(stream);
    }

    stream->buffer[stream->buffer_index] = (int)c;

    stream->off_written+=1;
    stream->buffer_index+=1;   
    stream->cursor+=1; 
    return c;
}