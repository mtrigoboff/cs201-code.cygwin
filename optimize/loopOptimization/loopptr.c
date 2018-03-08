// walks pointer through the array

#pragma GCC diagnostic ignored "-Wmisleading-indentation"

#include <stdio.h>
#include <time.h>
#include "iterations.h"

int     a[100] = {0};

int main(int argc, char** argv)
{
	int		i;
	int		*ptr;
	int		sum = 0;
	clock_t	start = clock();

    for (i = 0; i < ITERATIONS; i++)
        for (ptr = a; ptr < &a[100]; ptr++)
            sum += *ptr;

	printf("%.1f seconds\n",
		   (double) (clock() - start) / CLOCKS_PER_SEC);

	return sum;	// so optimizer will compile the code
}
