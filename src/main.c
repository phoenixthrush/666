#include <stdio.h>
#include <stdlib.h> // getenv

int main(int argc, char **argv) {
    #ifndef _WIN32
        printf("Not running on Windows. Exiting!\n");
        return 1;
    #endif

    char* homePath = getenv("USERPROFILE");
    
    if (homePath) {
        printf("Home directory: %s\n", homePath);
    } else {
        printf("Unable to retrieve home directory. Exiting!\n");
        return 1;
    }
}
