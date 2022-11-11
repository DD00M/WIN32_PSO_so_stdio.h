#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strsafe.h>
#include <stdbool.h>
#include <shlwapi.h>

#include "so_stdio.h"

SO_FILE *so_popen(const char *command, const char *type)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES si_pipe;
    DWORD dwRes;
    bool bRes;
    SO_FILE *file = (SO_FILE *)malloc(sizeof(SO_FILE));
    file->buffer_index = 0;
    file->off_written = 0;
    file->cursor = 0;
    file->firstIndex = 0;
    file->lastIndex = 0;
    strcpy(file->mode, type);
    file->is_p = 1;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si_pipe, sizeof(si_pipe));
    char result[128];
    char aux[16] = "cmd /c ";
    strcpy(result, aux);
    strcat(result, command);
    si_pipe.nLength = sizeof(si_pipe);
    si_pipe.bInheritHandle = TRUE;
    si_pipe.lpSecurityDescriptor = NULL;
    HANDLE readHandle;
    HANDLE writeHandle;
    
    CreatePipe(&readHandle, &writeHandle, &si_pipe, 0);
    if (strcmp(type, "r") == 0){
        file->so_handle = readHandle;
    }else if (strcmp(type, "w") == 0){
        file->so_handle = writeHandle;
    }

    if (strcmp(type, "r") == 0)
    {
        si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        si.hStdOutput = writeHandle;
        si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
        si.dwFlags |= STARTF_USESTDHANDLES;
        if (!SetHandleInformation(readHandle, HANDLE_FLAG_INHERIT, 0))
        {
            return NULL;
        }
        bRes = CreateProcessA(
                            NULL, 
                            result,
                            NULL,
                            NULL,
                            TRUE,
                            0,
                            NULL,
                            NULL,
                            &si,
                            &pi
                            );
        if (!bRes){
            printf("Create Process failed %d\n", GetLastError());
            return NULL;
        }else{
            CloseHandle(pi.hProcess);
            CloseHandle(writeHandle);
            file->p_pi = pi;
            return file;
        }    
    }
    else if (strcmp(type, "w") == 0)
    {
        si.hStdInput = readHandle;
        si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
        si.dwFlags |= STARTF_USESTDHANDLES;
        if (!SetHandleInformation(writeHandle, HANDLE_FLAG_INHERIT, 0))
        {
            return NULL;
        }  
        CloseHandle(writeHandle);
        bRes = CreateProcessA(
                            NULL, 
                            result,
                            NULL,
                            NULL,
                            TRUE,
                            0,
                            NULL,
                            NULL,
                            &si,
                            &pi
                            );    
        if (!bRes){
            printf("Create Process failed %d\n", GetLastError());
            return NULL;
        }else{
            CloseHandle(pi.hProcess);
            CloseHandle(readHandle);
            file->p_pi = pi;
            return file; 
        }     
    }
    else
        return NULL;
}