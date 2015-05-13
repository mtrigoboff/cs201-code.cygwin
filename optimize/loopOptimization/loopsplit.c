// a loop that has been split

#include <stdlib.h>

int     a[100] = {0};

int main(int argc, char** argv)
{
    int     n = 30000000;
    int     i, j;
    int     sum0 = 0;
    int     sum1 = 0;

    if (argc >= 2)
        n = atoi(argv[1]);

    for (i = 0; i < n; i++)
        for (j = 0; j < 100; j += 2) {
            sum0 += a[j];
            sum1 += a[j + 1];
            }

    return sum0 + sum1;
}
