.PHONY: all clean build
so_fopen.obj: so_fopen.c
    cl /c so_fopen.c
so_fgetc.obj: so_fgetc.c
    cl /c so_fgetc.c
so_fclose.obj: so_fclose.c
    cl /c so_fclose.c
so_fputc.obj: so_fputc.c
    cl /c so_fputc.c
so_fread.obj: so_fread.c
    cl /c so_fread.c
so_fwrite.obj: so_fwrite.c
    cl /c so_fwrite.c
so_fflush.obj: so_fflush.c
    cl /c so_fflush.c
so_fseek.obj: so_fseek.c
    cl /c so_fseek.c
so_popen.obj: so_popen.c
    cl /c so_popen.c
so_pclose.obj: so_pclose.c
    cl /c so_pclose.c
main.obj: main.c
    cl /c main.c
so_stdio.lib: so_fopen.obj so_fgetc.obj so_fclose.obj so_fputc.obj so_fread.obj so_fwrite.obj so_fflush.obj so_fseek.obj so_popen.obj so_pclose.obj
    link /nologo /dll so_fopen.obj so_fclose.obj so_fgetc.obj so_fputc.obj so_fread.obj so_fwrite.obj so_fflush.obj so_fseek.obj so_popen.obj so_pclose.obj /out:so_stdio.dll /implib:so_stdio.lib
main.exe: main.obj so_stdio.lib
    link /out:main.exe main.obj so_stdio.lib
build: so_fopen.obj so_fgetc.obj so_fclose.obj so_fputc.obj so_fread.obj so_fwrite.obj so_fflush.obj so_fseek.obj so_popen.obj so_pclose.obj
    link /nologo /dll so_fopen.obj so_fclose.obj so_fgetc.obj so_fputc.obj so_fread.obj so_fwrite.obj so_fflush.obj so_fseek.obj so_popen.obj so_pclose.obj /out:so_stdio.dll /implib:so_stdio.lib
clean: 
    del so_fopen.obj so_fclose.obj so_fgetc.obj so_stdio.dll so_stdio.exp so_stdio.lib main.exe main.obj so_fputc.obj so_fread.obj so_fwrite.obj so_fflush.obj so_fseek.obj so_popen.obj so_pclose.obj