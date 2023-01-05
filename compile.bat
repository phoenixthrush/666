del /q main.exe

windres source\manifest.rc source\manifest.o
gcc -o main source\main.c source\manifest.o -Wl,--subsystem=windows -Wall

del /q source\manifest.o