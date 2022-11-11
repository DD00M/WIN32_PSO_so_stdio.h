#include <windows.h>
#include "so_stdio.h"
#include <fileapi.h>
#include <stdbool.h>

#include <string.h>

#include <stdio.h>

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    if (strcmp(mode, "r") == 0)
    {
        // printf("1");
        SO_FILE *fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        if (fp == NULL)
        {
            // printf("2");
            perror("bad alloc\n");
            return NULL;
        }
        // printf("3");
        HANDLE h_in = CreateFileA(pathname,
                                  GENERIC_READ,
                                  FILE_SHARE_READ,
                                  NULL,
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL,
                                  NULL);
        // printf("4");
        if (h_in == INVALID_HANDLE_VALUE)
        {   
            // printf("5");
            perror("file could not be opened1\n");
            return NULL;
        }
        long size = 0;
        GetFileSizeEx(h_in, &size);
        fp->so_sizeFile = size;
        fp->buffer_index = 0;
        fp->so_handle = h_in;
        fp->cursor = 0;
        fp->firstIndex = 0;
        fp->lastIndex = 0;
        fp->childFlag = 0;
        fp->currentBufSize = 0;
        fp->is_file = 1;
        fp->is_p = 0;
        fp->isERR = 0;
        fp->off_read = 0;
        fp->off_written = 0;
        fp->pid = 0;
        fp->ppid = 0;
        fp->prev = 0;
        fp->eof = 0;
        fp->read_flag = 0;
        fp->so_start_offset = 0;
        fp->flagERR = 0;
        strcpy(fp->mode, "r");
        // printf("7");

        return fp;
    }
    else if (strcmp(mode, "r+") == 0)
    {
        // printf("1");
        SO_FILE *fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        if (fp == NULL)
        {
           // printf("2");
            perror("bad alloc\n");
            return NULL;
        }
        // printf("3");
        HANDLE h_in = CreateFileA(pathname,
                                  GENERIC_READ | GENERIC_WRITE,
                                  0,
                                  NULL,
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL,
                                  NULL);
        // printf("4");
        if (h_in == INVALID_HANDLE_VALUE)
        {
            //printf("5");
            perror("file could not be opened2\n");
            return NULL;
        }
        int size = 0;
        GetFileSizeEx(h_in, &size);
        fp->so_sizeFile = size;
        fp->buffer_index = 0;
        fp->so_handle = h_in;
        fp->cursor = 0;
        fp->firstIndex = 0;
        fp->lastIndex = 0;
        fp->childFlag = 0;
        fp->currentBufSize = 0;
        fp->is_p = 0;
        fp->isERR = 0;
        fp->off_read = 0;
        fp->off_written = 0;
        fp->is_file = 1;
        fp->pid = 0;
        fp->ppid = 0;
        fp->prev = 0;
        fp->eof = 0;
        fp->read_flag = 0;
        fp->so_start_offset = 0;
        fp->flagERR = 0;
        strcpy(fp->mode, "r+");
        // printf("7");

        return fp;
    }
    else if (strcmp(mode, "w") == 0)
    {
        SO_FILE *handle = (SO_FILE *)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL)
        {
            perror("bad alloc\n");
            return NULL;
        }
        else
        {
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if (found)
            {
                //printf("FLAG_PASSED\n");
                FindClose(check);

                HANDLE h_in = CreateFileA(pathname,
                                          GENERIC_WRITE | TRUNCATE_EXISTING,
                                          FILE_SHARE_WRITE,
                                          NULL,
                                          OPEN_EXISTING,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened3\n");
                    return NULL;
                }
                int size = 0;
                GetFileSizeEx(h_in, &size);
                handle->so_sizeFile = size;
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->is_file = 1;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->isERR = 0;
                handle->off_read = 0;
                handle->off_written = 0;
                handle->pid = 0;
                handle->ppid = 0;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                strcpy(handle->mode, "w");
            }
            else
            {
                //printf("FLAGNOTPASSED\n");

                HANDLE h_in = CreateFileA(pathname,
                                          GENERIC_WRITE,
                                          FILE_SHARE_WRITE,
                                          NULL,
                                          CREATE_NEW,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened4\n");
                    return NULL;
                }
                int size = 0;
                GetFileSizeEx(h_in, &size);
                handle->so_sizeFile = size;
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->isERR = 0;
                handle->is_file = 1;
                handle->off_read = 0;
                handle->off_written = 0;
                handle->pid = 0;
                handle->ppid = 0;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                strcpy(handle->mode, "w");
            }
            return handle;
        }
    }
    else if (strcmp(mode, "w+") == 0)
    {
        SO_FILE *handle = (SO_FILE *)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL)
        {
            perror("bad alloc\n");
            return NULL;
        }
        else
        {
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if (found)
            {
                //printf("FLAG_PASSED\n");
                FindClose(check);

                HANDLE h_in = CreateFileA(pathname,
                                          GENERIC_WRITE | GENERIC_READ | TRUNCATE_EXISTING,
                                          0,
                                          NULL,
                                          OPEN_EXISTING,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened5\n");
                    return NULL;
                }
                int size = 0;
                GetFileSizeEx(h_in, &size);
                handle->so_sizeFile = size;
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->is_file = 1;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->isERR = 0;
                handle->off_read = 0;
                handle->off_written = 0;
                handle->pid = 0;
                handle->ppid = 0;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                strcpy(handle->mode, "w+");
            }
            else
            {
                //printf("FLAGNOTPASSED\n");

                HANDLE h_in = CreateFileA(pathname,
                                          GENERIC_WRITE | GENERIC_READ,
                                          0,
                                          NULL,
                                          CREATE_NEW,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened6\n");
                    return NULL;
                }
                int size = 0;
                GetFileSizeEx(h_in, &size);
                handle->so_sizeFile = size;
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->isERR = 0;
                handle->off_read = 0;
                handle->is_file = 1;
                handle->off_written = 0;
                handle->pid = 0;
                handle->ppid = 0;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                strcpy(handle->mode, "w+");
            }
            return handle;
        }
    }
    else if (strcmp(mode, "a") == 0)
    {
        SO_FILE *handle = (SO_FILE *)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL)
        {
            perror("bad alloc\n");
            return NULL;
        }
        else
        {
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if (found)
            {
                //printf("FLAG_PASSED\n");
                FindClose(check);

                HANDLE h_in = CreateFileA(pathname,
                                          FILE_APPEND_DATA | GENERIC_WRITE,
                                          0x0,
                                          NULL,
                                          OPEN_EXISTING,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened7\n");
                    return NULL;
                }
                int size = 0;
                GetFileSizeEx(h_in, &size);
                handle->so_sizeFile = size;
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->is_file = 1;
                handle->isERR = 0;
                handle->off_read = 0;
                handle->off_written = 0;
                handle->pid = 0;
                handle->ppid = 0;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                strcpy(handle->mode, "a");
            }
            else
            {
                //printf("FLAGNOTPASSED\n");

                HANDLE h_in = CreateFileA(pathname,
                                          FILE_APPEND_DATA | GENERIC_WRITE,
                                          0,
                                          NULL,
                                          CREATE_NEW,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened8\n");
                    return NULL;
                }
                int size = 0;
                GetFileSizeEx(h_in, &size);
                handle->so_sizeFile = size;
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->isERR = 0;
                handle->off_read = 0;
                handle->off_written = 0;
                handle->pid = 0;
                handle->ppid = 0;
                handle->is_file = 1;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                strcpy(handle->mode, "a");
            }
            return handle;
        }
    }
    else if (strcmp(mode, "a+") == 0)
    {
        SO_FILE *handle = (SO_FILE *)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL)
        {
            perror("bad alloc\n");
            return NULL;
        }
        else
        {
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if (found)
            {
                //printf("FLAG_PASSED\n");
                FindClose(check);

                HANDLE h_in = CreateFileA(pathname,
                                          FILE_APPEND_DATA | GENERIC_READ | GENERIC_WRITE,
                                          0x0,
                                          NULL,
                                          OPEN_EXISTING,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened9\n");
                    return NULL;
                }
                int size = 0;
                GetFileSizeEx(h_in, &size);
                handle->so_sizeFile = size;
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->isERR = 0;
                handle->off_read = 0;
                handle->off_written = 0;
                handle->is_file = 1;
                handle->pid = 0;
                handle->ppid = 0;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                strcpy(handle->mode, "a+");
            }
            else
            {
                //printf("FLAGNOTPASSED\n");

                HANDLE h_in = CreateFileA(pathname,
                                          FILE_APPEND_DATA | GENERIC_READ | GENERIC_WRITE,
                                          0,
                                          NULL,
                                          CREATE_NEW,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);
                if (h_in == INVALID_HANDLE_VALUE)
                {
                    perror("file could not be opened10\n");
                    return NULL;
                }
                handle->buffer_index = 0;
                handle->so_handle = h_in;
                handle->cursor = 0;
                handle->firstIndex = 0;
                handle->lastIndex = 0;
                handle->childFlag = 0;
                handle->currentBufSize = 0;
                handle->is_p = 0;
                handle->isERR = 0;
                handle->off_read = 0;
                handle->off_written = 0;
                handle->pid = 0;
                handle->ppid = 0;
                handle->prev = 0;
                handle->read_flag = 0;
                handle->so_start_offset = 0;
                handle->flagERR = 0;
                handle->eof = 0;
                handle->is_file = 1;
                strcpy(handle->mode, "a+");
            }
            return handle;
        }
    }
    return NULL;
}
