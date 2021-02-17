// attempt to generate SNaN which failed because SNaNs apparently
// get converted to QNaNs by fld-fst sequence of operations

#include <stdio.h>

typedef union {
	int		i;
	float	f;
	}
Float4;

int main (int argc, char **argv)
{
	Float4	snan;
	Float4	qnan;
	short	cw;
	float	f;

	qnan.i = 0x7FC00000;	// QNaN value
	snan.i = 0x7F800001;	// SNaN value

	f = qnan.f;
	f += 1.0;

	f = snan.f;
	f += 1.0;				// we actually get a QNaN here

	// unmask all FPU exceptions but IM
	// (Invalid Operation apparently needs to
	//  stay masked for GDB to work properly)
    asm(
		"		fstcw	%[cwOut]			\n"
		"		andw	$0xFF01,%[cwOut]	\n"
		"		fldcw	%[cwIn]				\n"
		:	[cwOut]		"=m"	(cw)
		:	[cwIn]		"m"		(cw)
	);

	f = qnan.f;
	f += 1.0;

	f = snan.f;
	f += 1.0;				// we actually get a QNaN here

    return 0;
}
