#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strsafe.h>
#include <stdbool.h>
#include <shlwapi.h>
#include <synchapi.h>

#include "so_stdio.h"

int so_pclose(SO_FILE *stream)
{
    if (stream->is_p == 1)
    {
        int stat;
        HANDLE p_handle;
        int pid;
        if (stream->is_p == 1)
        {
            so_fclose(stream);
            stat = (int)WaitForSingleObject(stream->p_pi.hProcess, INFINITE);
            return (stat);
        }
    }
    else
    {
        perror("no so_popen was called\n");
        return -1;
    }
    return -1;
}