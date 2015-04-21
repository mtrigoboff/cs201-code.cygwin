// demonstrates jumping up the stack

#include <stdio.h>
#include <stdlib.h>

static int		nLevels = 3;
static int		retLevel;

void down(int n)
{
	printf("down(%d) called\n", n);
	if (n == 1) {
		retLevel = 1;
		printf("down(%d) jumping up the stack to main()\n", n);
		asm(
			"		movl	%[nLevels], %%eax		\n"
			"	up:	movl	(%%ebp), %%ebp			\n"
			"		dec		%%eax					\n"
			"		cmp		$1, %%eax				\n"
			"		jne		up						\n"
			"		movl	%%ebp, %%esp			\n"
			"		pop		%%ebp					\n"
			"		ret								\n"
		:											// no outputs
		:	[nLevels]	"m"		(nLevels)			// input
		: "eax"										// clobber
		);
		}
	else {
		down(n - 1);
		printf("down(%d) returning\n", n);
		}
}

int main(int argc, char **argv)
{
	if (argc > 1)
		nLevels = atoi(argv[1]);

	printf("main() about to call down(%d)\n", nLevels);
	down(nLevels);
	printf("down(%d) returned to main()\n", retLevel);

	return 0;
}
