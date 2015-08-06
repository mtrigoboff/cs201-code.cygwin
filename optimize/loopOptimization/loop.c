// original loop

#include <stdio.h>
#include <time.h>
#include "iterations.h"

int     a[100] = {0};

int main(int argc, char** argv)
{
	int		i, j;
	int		sum = 0;
	clock_t	start = clock();

	for (i = 0; i < ITERATIONS; i++)
		for (j = 0; j < 100; j++)
			sum += a[j];

	printf("%.1f seconds\n",
		   (double) (clock() - start) / CLOCKS_PER_SEC);

	return sum;
}
