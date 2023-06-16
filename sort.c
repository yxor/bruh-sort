#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef unsigned int uint;

/*Return the unsigned absolute value of X.*/
uint uabs(const int in){
    const uint out = (uint)in;
    return in < 0 ? -out : out;
}

// this should be the path to the sleep binary
#define SLEEP_PATH "/root/bruh/sleep"

int main(uint argc, char** argv)
{
    if(argc < 2)
    {
        //empty arrays are forbidden
        fprintf(stderr, "bruh");
        exit(EXIT_FAILURE);
    }
    printf("unsorted array:\n");
    const uint n = argc;
    int min = atoi(argv[1]);
    const arr_len = n - 1;
    uint *arr = malloc(arr_len * sizeof(uint));
    for(uint i = 1; i < n; i++)
    {
        int tmp = atoi(argv[i]);
        arr[i-1] = (uint)tmp;
        //for negative support
        if(tmp < min)
            min = tmp;
        printf("%s ", argv[i]);
    }
    const uint offset = uabs(min);
    printf("\nsorted array:\n");
    //sorting time
    for(uint i = 0; i < arr_len; i++)
    {
        switch(fork())
        {
            case -1:
                fprintf(stderr, "fork failed");
                exit(EXIT_FAILURE);
            case 0:
                execl(SLEEP_PATH, "sleep", itoa(arr[i] + offset), NULL);
        }
    }

    for(uint i = 1; i < n; i++)
        wait(NULL);
    printf("\n");
    return 0;

}
