#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef unsigned int uint;

//Return the unsigned absolute value of X.
uint uabs(const int in){
    const uint out = (uint)in;
    return in < 0 ? -out : out;
}

//Convert an unsigned integer to a decimal string.
char* utoa(uint n)
{
    if (n == 0u)
        return "0";
    u_int8_t i;
    //`(1<<32)-1` has 10 digits.
    //this will sometimes be a negligible "soft" memory-leak.
    char s[11u];
    while (n > 0u)
    {
        s[i++] = '0' + (n % 10u);
        n /= 10u;
    };
    s[i]='\0';
    return s;
};

// this should be the path to the sleep binary
#define SLEEP_PATH "/root/bruh/sleep"

int main(int argc, char** argv)
{
    const uint n = (uint)argc;
    if(n < 2u)
    {
        fprintf(stderr, "bruh");
        exit(EXIT_FAILURE);
    }
    printf("unsorted array:\n");
    int min = atoi(argv[1]);
    const uint arr_len = n - 1u;
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
                execl(SLEEP_PATH, "sleep", utoa(arr[i] + offset), NULL);
        }
    }
    free(arr);
    arr = NULL;

    for(uint i = 1; i < n; i++)
        wait(NULL);
    printf("\n");
    return 0;

}
