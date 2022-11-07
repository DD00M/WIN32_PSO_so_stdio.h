#include <windows.h>
#include "so_stdio.h"

#include <stdbool.h>

#include <string.h>

#include <stdio.h>

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    if (strcmp(mode, "r") == 0){
        printf("1");
        SO_FILE *fp = (SO_FILE*)malloc(sizeof(SO_FILE));
        if (fp == NULL){
            printf("2");
            perror("bad alloc\n");
            return NULL;
        }
        printf("3");
        HANDLE h_in = CreateFileA(pathname, 
                                GENERIC_READ, 
                                FILE_SHARE_READ, 
                                NULL, 
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );    
        printf("4");
        if (h_in == INVALID_HANDLE_VALUE){
            printf("5");
            perror("file could not be opened\n");
            return NULL;
        }
        fp->buffer_index = 0;
        fp->so_handle = h_in;
        fp->cursor = 0;
        fp->firstIndex = 0;
        fp->lastIndex = 0;
        printf("6");
        fp->buffer = (char*)malloc(BUFSIZE*sizeof(char));
        //fp->buffer[BUFSIZE] = '\0';
        if(fp->buffer == NULL){
            perror("bad alloc buffer\n");
            return NULL;
        }
        fp->mode = "r";
        printf("7");
    
        return fp;
    }else if(strcmp(mode, "r+") == 0){
        printf("1");
        SO_FILE *fp = (SO_FILE*)malloc(sizeof(SO_FILE));
        if (fp == NULL){
            printf("2");
            perror("bad alloc\n");
            return NULL;
        }
        printf("3");
        HANDLE h_in = CreateFileA(pathname, 
                                GENERIC_READ | GENERIC_WRITE, 
                                0, 
                                NULL, 
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );    
        printf("4");
        if (h_in == INVALID_HANDLE_VALUE){
            printf("5");
            perror("file could not be opened\n");
            return NULL;
        }
        fp->buffer_index = 0;
        fp->so_handle = h_in;
        fp->firstIndex = 0;
        fp->cursor = 0;
        printf("6");
        fp->buffer = (char*)malloc(BUFSIZE*sizeof(char));
        if(fp->buffer == NULL){
            perror("bad alloc buffer\n");
            return NULL;
        }
        fp->mode = "r+";
        printf("7");
    
        return fp;
    }else if(strcmp(mode, "w") == 0){
        SO_FILE *handle = (SO_FILE*)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL){
            perror("bad alloc\n");
            return NULL;
        }else{
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if(found){
                printf("FLAG_PASSED\n");
                FindClose(check);

            HANDLE h_in = CreateFileA(pathname, 
                                GENERIC_WRITE | TRUNCATE_EXISTING, 
                                FILE_SHARE_WRITE, 
                                NULL, 
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "w";
            handle->cursor = 0;
            handle->firstIndex = 0;
            }else{
                printf("FLAGNOTPASSED\n");

            HANDLE h_in = CreateFileA(pathname, 
                                GENERIC_WRITE, 
                                FILE_SHARE_WRITE, 
                                NULL, 
                                CREATE_NEW, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "w";    
            handle->cursor = 0;
            handle->firstIndex = 0;
            }
        return handle;
        }
    }else if(strcmp(mode, "w+") == 0){
        SO_FILE *handle = (SO_FILE*)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL){
            perror("bad alloc\n");
            return NULL;
        }else{
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if(found){
                printf("FLAG_PASSED\n");
                FindClose(check);

            HANDLE h_in = CreateFileA(pathname, 
                                GENERIC_WRITE | GENERIC_READ | TRUNCATE_EXISTING, 
                                0, 
                                NULL, 
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "w+";
            handle->cursor = 0;
            handle->firstIndex = 0;
            }else{
                printf("FLAGNOTPASSED\n");

            HANDLE h_in = CreateFileA(pathname, 
                                GENERIC_WRITE | GENERIC_READ, 
                                0, 
                                NULL, 
                                CREATE_NEW, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "w+";  
            handle->cursor = 0;  
            handle->firstIndex = 0;
            }
        return handle;
        }
    }else if(strcmp(mode, "a") == 0){
        SO_FILE *handle = (SO_FILE*)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL){
            perror("bad alloc\n");
            return NULL;
        }else{
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if(found){
                printf("FLAG_PASSED\n");
                FindClose(check);

            HANDLE h_in = CreateFileA(pathname, 
                                FILE_APPEND_DATA, 
                                0x0, 
                                NULL, 
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "a";
            handle->cursor = 0;
            handle->firstIndex = 0;
            }else{
                printf("FLAGNOTPASSED\n");

            HANDLE h_in = CreateFileA(pathname, 
                                FILE_APPEND_DATA, 
                                0, 
                                NULL, 
                                CREATE_NEW, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "a"; 
            handle->cursor = 0; 
            handle->firstIndex = 0; 
            }
        return handle;
        }        
    }else if(strcmp(mode, "a+") == 0){
        SO_FILE *handle = (SO_FILE*)malloc(sizeof(SO_FILE));
        handle->buffer_index = 0;
        if (handle == NULL){
            perror("bad alloc\n");
            return NULL;
        }else{
            WIN32_FIND_DATA find_file_data;
            HANDLE check = FindFirstFile(pathname, &find_file_data);
            int found = check != INVALID_HANDLE_VALUE;
            if(found){
                printf("FLAG_PASSED\n");
                FindClose(check);

            HANDLE h_in = CreateFileA(pathname, 
                                FILE_APPEND_DATA | GENERIC_READ, 
                                0x0, 
                                NULL, 
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "a+";
            handle->cursor = 0;
            handle->firstIndex = 0;
            }else{
                printf("FLAGNOTPASSED\n");

            HANDLE h_in = CreateFileA(pathname, 
                                FILE_APPEND_DATA | GENERIC_READ, 
                                0, 
                                NULL, 
                                CREATE_NEW, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL
                                );            
            if (h_in == INVALID_HANDLE_VALUE){
                perror("file could not be opened\n");
                return NULL;
            }
            handle->so_handle = h_in;
            handle->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            handle->mode = "a+";
            handle->cursor = 0;  
            handle->firstIndex = 0;  
            }
        return handle;
        }
    }
    return NULL;
}
