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
        for (j = 0; j < 100; j += 10) {
            a[j] += 3;
            a[j + 1] += 3;
            a[j + 2] += 3;
            a[j + 3] += 3;
            a[j + 4] += 3;
            a[j + 5] += 3;
            a[j + 6] += 3;
            a[j + 7] += 3;
            a[j + 8] += 3;
            a[j + 9] += 3;
            }

    return 0;
}
