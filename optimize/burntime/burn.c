// burn up time uselessly

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	// if arg[1] present, use as number of iterations
	int			iterations = argc > 1 ? atoi(argv[1]) : 10000000;
	double		burn = 1.0;

	printf("%d iterations\n", iterations);

	// burn up time
	for (int i = 0; i < iterations; i++)
		burn *= 3.0; 

	return 0;
}
