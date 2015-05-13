// walks pointer through the array

#include <stdlib.h>

int     a[100] = {0};

int main(int argc, char** argv)
{
    int     n = 30000000;
    int     i;
    int     *ptr;
    int     sum = 0;

    if (argc >= 2)
        n = atoi(argv[1]);

    for (i = 0; i < n; i++)
        for (ptr = a; ptr < &a[100]; ptr++)
            sum += *ptr;

    return sum;
}
