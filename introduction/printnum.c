// prints number with requested precision

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	double	number;
	int		precision;

	//check for correct number of command line arguments
	if (argc != 3) {
		printf("call as: printnum <number> <precision>\n");
		return -1;
		}

	// get numerical values of command line arguments
	number = atof(argv[1]);
	precision = atoi(argv[2]);
    
	printf("number = %.*f\n", precision, number);
    return 0;
}
