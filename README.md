# bruh-sort
Sorting algorithm using POSIX system calls. AKA "sleep-sort" and "lazy-sort".

## how does it work ?

Compile using the gcc compiler 

```sh
gcc sleep.c -o sleep -Wall -Werror
gcc sort.c -o sort -Wall -Werror
```

Then, run the program with a list of unsigned integers as arguments. (negative integers support coming soon)

```sh
./sort 9 8 7 6 5 3 4 1 2 0
```
