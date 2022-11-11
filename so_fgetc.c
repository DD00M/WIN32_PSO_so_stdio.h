#include <windows.h>

#include <string.h>
#include "so_stdio.h"

#include <stdio.h>

int so_fgetc(SO_FILE *stream)
{
    if (stream == NULL){
        return SO_EOF;
    }
    if (strcmp(stream->mode, "w") == 0){
        return SO_EOF;
    }
    if (stream->prev == WRITEprev){
        so_fflush(stream);
        stream->prev = READprev;
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
        //printf("\n\nSTREAM BUFFER: %d\n\n%s",checkRead, stream->buffer);
        if (checkRead < 0){
            printf("err checkRead\n");
            return SO_EOF;
        }
        stream->lastIndex = (int)bytesRead - 1;
        stream->firstIndex = 0;
        stream->buffer_index = 0;
        if (stream->lastIndex == -1){
            return SO_EOF;
        }
        if (checkRead && bytesRead == 0){
            stream->eof = 1;
            return SO_EOF;
        }
        else if (bytesRead < 0)
        {
            stream->flagERR = -1;
            return SO_EOF;
        }
        else
        {
            stream->buffer_index = 0;
            stream->off_read = bytesRead;
            stream->cursor+=1;
            return (int)stream->buffer[0];
        }
    }
    else
    {
        stream->firstIndex += 1;
        stream->buffer_index += 1;
        stream->cursor+=1;
        return (int)stream->buffer[stream->firstIndex];
    }
}