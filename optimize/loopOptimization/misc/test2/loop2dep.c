// a loop that has been unrolled, which both:
//
//     * lowers the loop control overhead per "iteration", and
//
//     * provides an opportunity for the Pentium's built-in
//           parallel processing capabilities

#include <stdlib.h>

int     a[100] = {0};

int main (int argc, char** argv)
{
    int     n = 100000;
    int     i, j;

    if (argc >= 2)
        n = atoi(argv[1]);

    for (i = 0; i < n; i++)
        for (j = 0; j < 100; ) {
            a[j++] *= 3;
            a[j++] *= 3;
            a[j++] *= 3;
            a[j++] *= 3;
            }

    return 0;
}
