// recursive implementation of factorial that computes
//   its result "on the way down"

#include <stdlib.h>
#include <stdio.h>

int fact(int n, int result)
{
    if (n <= 1)
        return result;
    else
        return fact(n - 1, result * n);
}

int main(int argc, char **argv)
{
    int     n = argc > 1 ? atoi(argv[1]) : -1;
    int     f;

    if (n < 0) {
        printf("one numeric argument is required\n");
        return -1;
        }

    f = fact(n, 1);

    printf("fact(%u) = %6u\n", n, f);
    return 0;
}
