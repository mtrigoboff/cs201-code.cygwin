// standard recursive implementation of factorial

#include <stdlib.h>
#include <stdio.h>

int fact(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * fact(n - 1);
}

int main(int argc, char **argv)
{
    int     n = argc > 1 ? atoi(argv[1]) : -1;
    int     f;

    if (n < 0) {
        printf("one numeric argument is required\n");
        return -1;
        }

    f = fact(n);

    printf("fact(%u) = %6u\n", n, f);
    return 0;
}
