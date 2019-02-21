#include <stdio.h>

typedef void (*FnPtr)(int* n);

static void incr(int* n)
{
	printf("incr\n");
	(*n)++;
}

static void decr(int* n)
{
	printf("decr\n");
	(*n)--;
}

int main()
{
	FnPtr	fPtr;
	int		n = 3;

	printf("n = %d\n\n", n);

	fPtr = incr;
	(*fPtr)(&n);
	printf("n = %d\n\n", n);

	fPtr = decr;
	(*fPtr)(&n);
	printf("n = %d\n\n", n);

	return 0;
}
