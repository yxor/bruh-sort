#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef unsigned int uint;

//Swaps char pointed by `a` with the one pointed by `b`.
//To use with strings, call iteratively.
void swap_chars(char* a, char* b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
};

//Reverse a string in-place.
//len is the number of chars to reverse (excluding the NULL terminator).
void strrev_in_place(char* s, const size_t len)
{
    for (size_t i; i < len/2; i++)
        swap_chars(s+i, s+(len-1-i));
};

//Convert an unsigned integer to a decimal string.
char* utoa(uint n)
{
    if (n == 0u)
        return "0";
    u_int8_t i;
    //`(1<<32)-1` has 10 digits.
    //this will sometimes be a negligible "soft" memory-leak.
    static char s[11u];
    while (n > 0u)
    {
        s[i++] = '0' + (n % 10u);
        n /= 10u;
    };
    //just-in-case, because of static
    s[i]='\0';
    strrev_in_place(s, i);
    return s;
};

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
    const uint offset = min < 0 ? -(uint)min : 0u;
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
                execl(
                    "./sleep", "sleep",
                    utoa(arr[i] + offset), argv[i+1],
                NULL);
        }
    }
    free(arr);
    arr = NULL;

    for(uint i = 1; i < n; i++)
        wait(NULL);
    printf("\n");
    return 0;

}
