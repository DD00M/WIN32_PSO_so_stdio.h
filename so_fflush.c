
#include <windows.h>

#include <stdlib.h> /* exit */
#include <string.h>

#include "so_stdio.h"

#include <stdio.h>

int so_fflush(SO_FILE *stream)
{
    if (stream->off_written != 0)
    {
        DWORD bytesWrite;
        int check = WriteFile(stream->so_handle, stream->buffer, BUFSIZE, &bytesWrite, NULL);
        if(check <= 0){
            return SO_EOF;
        }
        stream->off_written = 0;
        return 0;
    }else{
        return SO_EOF;
    }
}