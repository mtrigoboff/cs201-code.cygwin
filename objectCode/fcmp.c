// demonstrates older-style floating point comparison,
// which dates from when the FPU was a separate chip

#include <stdlib.h>

int main(int argc, char** argv)
{
	float	f1;
	float	f2;

	if (argc == 3) {
		f1 = atof(argv[1]);
		f2 = atof(argv[2]);
		}
	else {
		f1 = 4.0;
		f2 = 3.0;
		}
	
	asm("		flds	%[f1]		\n"
		"		flds	%[f2]		\n"
		"		fcompp				\n"
		"		fstsw	%%ax		\n"
		"		sahf				\n"
		"		ja		j1			\n"
		"		nop					\n"
		"		jmp		j2			\n"
		" j1:	nop					\n"
		" j2:	nop					\n"
		:
		: [f1]		"m"		(f1),
		  [f2]		"m"		(f2)
	);

	return 0;
}

