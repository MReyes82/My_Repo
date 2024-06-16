#include "util.h"

#include <stdlib.h>

OS_Type get_os(void)
{
    #if defined(_WIN32) || defined(_WIN64)
        return WINDOWS;

    #elif defined(__linux__)
        return LINUX;

    
    #elif defined(__APPLE__) || defined(__MACH__)
        return MAC;

    #else
        return UNKNOWN;

    #endif
}

void clear_terminal(void)
{
    OS_Type os = get_os();

    switch (os)
    {
        case WINDOWS:
            system("cls");
            break;

        case LINUX:

        case MAC:
            system("clear");
            break;

        default:
            // stop the program if the OS is unknown
            printf("Unknown OS\n");
            exit(EXIT_FAILURE);
            break;
    }

    return;
}