// a loop that has been split

#pragma GCC diagnostic ignored "-Wmisleading-indentation"

#include <stdio.h>
#include <time.h>
#include "iterations.h"

int     a[100] = {0};

int main(int argc, char** argv)
{
	int		i, j;
	int		sum0 = 0;
	int		sum1 = 0;
	clock_t	start = clock();

    for (i = 0; i < ITERATIONS; i++)
        for (j = 0; j < 100; j += 2) {
            sum0 += a[j];
            sum1 += a[j + 1];
            }

	printf("%.1f seconds\n",
		   (double) (clock() - start) / CLOCKS_PER_SEC);

    return sum0 + sum1;	// so optimizer will compile the code
}
