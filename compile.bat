del /q 666.exe

windres source\manifest.rc source\manifest.o
gcc -o 666 source\main.c source\manifest.o -Wl,--subsystem=windows -Wall

del /q source\manifest.o
