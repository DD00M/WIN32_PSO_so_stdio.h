#include "so_stdio.h"

int so_fseek(SO_FILE *stream, long offset, int whence){
    if (stream->prev == READprev){
        so_fflush(stream);
    }
    if (stream->prev == WRITEprev){
        so_fflush(stream);
    }

    unsigned int pos = (unsigned int)so_ftell(stream);
    int limit = GetFileSize(stream->so_handle, NULL);

    stream->cursor = (unsigned int)SetFilePointer(stream->so_handle, offset, NULL, whence);
    if(stream->cursor < 0)
    {
        stream->isERR = 999;
        return SO_EOF;
    }else if (stream->cursor > limit){
        stream->isERR = 999;
        return SO_EOF;
    }
    return 0;
}