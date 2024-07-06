#include <limits.h>
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
//`len` is the number of chars to reverse (excluding `NULL` terminator).
void strrev_in_place(char* s, const size_t len)
{
    for (size_t i = 0u; i < len/2u; i++)
        swap_chars(s + i, s + (len-1 - i));
};

//(decimal)
const u_int8_t UINT32_MAX_DIGITS = 10u;
const u_int8_t BUF_SIZE = UINT32_MAX_DIGITS + 1u;

//Format uint32 to decimal string.
//`s` is the buffer where the digits will be placed.
//`s` will end with NULL, for convenience.
void u32toa(u_int32_t n, char s[BUF_SIZE])
{
    u_int8_t i = 0u;
    while(1)
    {
        s[i++] = '0' + (n % 10u);
        if ((n /= 10u) == 0u)
        {
            s[i] = '\0';
            // convert to big-endian
            strrev_in_place(s, i);
            return;
        };
    };
};

int main(const int argc, const char** argv)
{
    const uint n = (uint)argc;
    if(n < 2u)
    {
        fprintf(stderr, "bruh");
        exit(EXIT_FAILURE);
    };
    printf("unsorted array:\n");
    int min = atoi(argv[1]);
    const uint arr_len = n - 1u;
    u_int32_t* arr = malloc(arr_len * sizeof(u_int32_t));
    for(uint i = 1; i < n; i++)
    {
        int tmp = atoi(argv[i]);
        arr[i-1] = (uint)tmp;
        //support negatives
        if(tmp < min)
            min = tmp; //clamp
        printf("%s ", argv[i]);
    };
    const uint offset = min < 0 ? -(uint)min : 0u;
    printf("\nsorted array:\n");
    // sorting time
    for(uint i = 0; i < arr_len; i++)
    {
        switch(fork())
        {
            case -1:
                fprintf(stderr, "fork failed");
                exit(EXIT_FAILURE);
            case 0: {
                char s[BUF_SIZE];
                u32toa(arr[i] + offset, s);
                execl(
                    "./sleep", "sleep",
                    s, argv[i+1],
                NULL);
            }
        };
    };
    free(arr);
    // "safety"
    arr = NULL;

    for(uint i = 1; i < n; i++)
        wait(NULL);
    printf("\n");
    return 0;

}
