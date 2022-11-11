
#include <windows.h>

#include <stdlib.h> /* exit */
#include <string.h>

#include "so_stdio.h"

#include <stdio.h>

int so_fflush(SO_FILE *stream)
{
    if (stream->prev == WRITEprev)
    {
        if (stream->off_written != 0)
        {
            DWORD bytesWrite;
            int d = WriteFile(stream->so_handle, stream->buffer, stream->off_written, &bytesWrite, NULL);
            if (d < 0)
            {
                stream->isERR = 555;
                return SO_EOF;
            }
            stream->buffer_index = 0;
            stream->off_written = 0;
            // memset(stream->buffer, 0, BUFSIZE);
            for (int i = 0; i < BUFSIZE; i++)
            {
                stream->buffer[i] = '\0';
            }
            stream->isERR = 999;
            return 0;
        }return SO_EOF;
    }
    else
    {
        stream->buffer_index = 0;
        stream->off_written = 0;
            // memset(stream->buffer, 0, BUFSIZE);
        for (int i = 0; i < BUFSIZE; i++)
        {
            stream->buffer[i] = '\0';
        }

        stream->isERR = 555;
        return SO_EOF;
    }
}