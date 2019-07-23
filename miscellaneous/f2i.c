#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	float	f;
	int		i;

	if (argc != 2) {
		printf("need fp # cmd line arg\n");
		return 1;
		}
	f = atof(argv[1]);
	i = f;
	printf("%i : %.2f\n", i, f);
	return 0;
}
