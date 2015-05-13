// a loop that has been unrolled

#include <stdlib.h>

int     a[100] = {0};

int main(int argc, char** argv)
{
    int     n = 30000000;
    int     i, j;
    int     sum = 0;

    if (argc >= 2)
        n = atoi(argv[1]);

    for (i = 0; i < n; i++)
        for (j = 0; j < 100; j += 4) {
            sum += a[j];
            sum += a[j + 1];
            sum += a[j + 2];
            sum += a[j + 3];
            }

    return sum;
}
