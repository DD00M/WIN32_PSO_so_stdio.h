#include <windows.h>
#include <string.h>

#include "so_stdio.h"

#include <stdio.h>

int so_fputc(int c, SO_FILE *stream)
{
    if (strcmp(stream->mode, "r") == 0){
        return SO_EOF;
    }
    if (stream->buffer_index < BUFSIZE){
        stream->buffer[stream->buffer_index] = (char)c;
        stream->buffer_index += 1;
        stream->cursor += 1;
        stream->off_written += 1;
        return c;
    }else{
        DWORD bytesWrite;
        int check = WriteFile(stream->so_handle, stream->buffer, BUFSIZE, &bytesWrite, NULL);
        if (check <= 0){
            return SO_EOF;
        }
        stream->buffer_index = 0;
        stream->cursor += 1;
        stream->off_written += BUFSIZE;
        return c;
    }
}