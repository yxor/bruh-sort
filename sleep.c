#include <sys/fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#if _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

typedef unsigned int uint;

int main(uint argc, char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "wrong number of args");
        exit(EXIT_FAILURE);
    }
    uint sleeping_time = (uint)atoi(argv[1]);
    #if _WIN32
    Sleep(sleeping_time);
    #else
    usleep(sleeping_time * 5000);
    #endif
    printf("%d ", sleeping_time);
    return 0;
}
