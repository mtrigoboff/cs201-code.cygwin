// a loop that has not been unrolled

#include <stdlib.h>

int     a[100] = {0};

int main (int argc, char** argv)
{
    int     n = 100000;
    int     i, j;

    if (argc >= 2)
        n = atoi(argv[1]);

    for (i = 0; i < n; i++)
        for (j = 0; j < 100; j++)
            a[j] *= 3;

    return 0;
}
