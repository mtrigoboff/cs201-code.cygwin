#include <stdio.h>
#include <stdlib.h>

typedef union {
	int		i;
	float	f;
} Convert;

int main(int argc, char** argv)
{
	Convert	cvt;
	float	f = argc > 1 ? atof(argv[1]) : 0;
	int		i;

	// use pointer
	i = *((int *) &f);
	printf("0x%08X\n", i);

	// use union
	cvt.f = f;
	i = cvt.i;
	printf("0x%08X\n", i);

	return 0;
}
