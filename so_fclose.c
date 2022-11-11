#include <windows.h>
#include "so_stdio.h"

#include <stdbool.h>

#include <string.h>

#include <stdio.h>

int so_fclose(SO_FILE *stream)
{
    if (stream == NULL){
        return SO_EOF;
    }

    if (stream->is_file == 0){
        return SO_EOF;
    }

    so_fflush(stream);
    BOOL k = CloseHandle(stream->so_handle);
    if (!k)
    {
        free(stream);
        return SO_EOF;
    }
    free(stream);
    return 0;
}