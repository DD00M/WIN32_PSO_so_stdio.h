#include <windows.h>

#include <string.h>
#include "so_stdio.h"

#include <stdio.h>

int so_fgetc(SO_FILE *stream)
{
    //printf("salut din fgetc\n");
    if (strcmp(stream->mode, "w") == 0){
        return SO_EOF;
    }
    //printf("%d %d\n", stream->firstIndex, stream->lastIndex);
    if (stream->firstIndex == stream->lastIndex)
    {
        //printf("fgetc\n");
        DWORD bytesRead = -1;
        int checkRead = ReadFile(stream->so_handle, 
                                stream->buffer, 
                                BUFSIZE, 
                                &bytesRead, 
                                NULL
                                );
        //printf("$$$$\n");
        //printf("%s\n", stream->buffer);
        //printf("%d\n", bytesRead);
        if(checkRead == 0){
            return SO_EOF;
        }
        if(bytesRead == 0){
            return SO_EOF;
        }
        stream->lastIndex = (int)bytesRead - 1;
        stream->firstIndex = 0;
        //printf("%d %d\n", stream->firstIndex, stream->lastIndex);
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
            //printf("this_Char: %c", stream->buffer[0]);
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