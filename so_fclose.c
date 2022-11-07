#include <windows.h>
#include "so_stdio.h"

#include <stdbool.h>

#include <string.h>

#include <stdio.h>

int so_fclose(SO_FILE *stream)
{
    free(stream);
    if (stream != NULL){
        CloseHandle(stream->so_handle);
        return SO_EOF;
    }else return 0;
}