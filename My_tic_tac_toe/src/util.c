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
        return -1;

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
            printf("Unknown OS\n");
            break;
    }

    return;
}