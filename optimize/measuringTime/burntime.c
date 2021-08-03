// burn up time uselessly

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>           // for clock()

int burnTime(int seconds, bool debug)
{
	clock_t		startTime = clock();
	clock_t		stopTime = startTime + seconds * CLOCKS_PER_SEC;
	int			burn = 1;
	int			iterations = 0;

	if (stopTime < startTime) {
		printf("clock wrapped around, try again\n");
		return -1;
		}

	if (debug)		// print debugging info
		printf("seconds: %d, startTime: %lu, stopTime: %lu"
			   ", CLOCKS_PER_SEC: %lu\n",
			   seconds, startTime, stopTime, CLOCKS_PER_SEC);

	// burn up time
	while(clock() < stopTime) {
		burn *= 3; 
		iterations++;
		}
	
	return iterations;
}

#ifdef TEST
int main(int argc, char **argv)
{
	// if arg[1] present, use as number of seconds
	int			seconds = argc > 1 ? atoi(argv[1]) : 3;       
	int			iterations;

	iterations = burnTime(seconds, argc > 2);
	printf("iterations: %d\n", iterations);
	return 0;
}
#endif
