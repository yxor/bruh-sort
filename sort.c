#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    if(argc < 2)
    {
        fprintf(stderr, "bruh");
        exit(EXIT_FAILURE);
    }
    int n = argc;
    printf("unsorted array:\n");
    for(int i = 1; i < n; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\nsorted array:\n");
    //sorting time
    for(int i = 1; i < n; i++)
    {
        switch(fork())
        {
            case -1:
                fprintf(stderr, "fork failed");
                exit(EXIT_FAILURE);
            case 0:
                execl("/root/bruh/sleep", "sleep", argv[i], NULL);
        }
    }

    for(int i = 1; i < n; i++)
        wait(NULL);
    printf("\n");
    return 0;

}
