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

//increases sorting accuracy
const uint DELAY_FACTOR = 4;

/* Sleep __miliseconds miliseconds, or until a signal arrives that is not blocked
   or ignored.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
int msleep(int __miliseconds)
{
    return usleep(__miliseconds * 1000);
};

int main(const int argc, const char** argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "wrong number of args");
        exit(EXIT_FAILURE);
    }
    uint sleeping_time = (uint)(atoi(argv[1])) * DELAY_FACTOR;
    #if _WIN32
    Sleep(sleeping_time);
    #else
    msleep(sleeping_time);
    #endif
    printf("%d ", sleeping_time);
    return 0;
}
