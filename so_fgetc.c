#include <windows.h>

#include <string.h>
#include "so_stdio.h"

#include <stdio.h>

int so_fgetc(SO_FILE *stream)
{
    if (strcmp(stream->mode, "w") == 0){
        return SO_EOF;
    }
   if (stream->firstIndex == stream->lastIndex)
    {
        DWORD bytesRead = -1;
        int checkRead = ReadFile(stream->so_handle, 
                                stream->buffer, 
                                BUFSIZE, 
                                &bytesRead, 
                                NULL
                                );
        if(checkRead == 0){
            return SO_EOF;
        }
        if(bytesRead == 0){
            return SO_EOF;
        }
        stream->lastIndex = (int)bytesRead - 1;
        stream->firstIndex = 0;
        if (stream->lastIndex == -1){
            return NULL;
        }
        if (bytesRead <= 0)
        {
            return SO_EOF;
        }
        else
        {
            stream->off_read = bytesRead;
            stream->cursor += 1;
            return (int)stream->buffer[0];
        }
    }
    else
    {
        stream->firstIndex += 1;
        stream->buffer_index += 1;
        stream->cursor += 1;
        return (int)stream->buffer[stream->firstIndex];
    }
}