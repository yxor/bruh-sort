#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef unsigned int uint;

// this should be the path to the sleep binary
#define SLEEP_PATH "/root/bruh/sleep"

int main(uint argc, char** argv){
    if(argc < 2)
    {
        fprintf(stderr, "bruh");
        exit(EXIT_FAILURE);
    }
    uint n = argc;
    printf("unsorted array:\n");
    for(uint i = 1; i < n; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\nsorted array:\n");
    //sorting time
    for(uint i = 1; i < n; i++)
    {
        switch(fork())
        {
            case -1:
                fprintf(stderr, "fork failed");
                exit(EXIT_FAILURE);
            case 0:
                execl(SLEEP_PATH, "sleep", argv[i], NULL);
        }
    }

    for(uint i = 1; i < n; i++)
        wait(NULL);
    printf("\n");
    return 0;

}
