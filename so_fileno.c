#include "so_stdio.h"


HANDLE so_fileno(SO_FILE *stream)
{
    if (stream == NULL){
        return SO_EOF;
    }
    if (stream->so_handle != 0)
    {
        stream->isERR = 888;
        return stream->so_handle;
    }else {stream->isERR = 555; return -1;};
}