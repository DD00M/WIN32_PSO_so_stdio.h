#include "so_stdio.h"

HANDLE so_fileno(SO_FILE *stream){
    return stream->so_handle;
}