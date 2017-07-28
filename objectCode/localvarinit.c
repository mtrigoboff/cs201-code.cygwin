// demonstrates the initialization of local variablle space
// in the stack frame to 0xCCCCCCCC

int fn()
{
   int		x = 0xDDDDDDDD;
   int		y = 0xEEEEEEEE;
   int		z = 0xFFFFFFFF;

    // fill array with new character
	asm("	cld								\n"		// set to increment
		"	mov     	%%esp, %%edi		\n"
		"	mov     	$0xCCCCCCCC, %%eax	\n"
		"	mov     	%%ebp, %%ecx		\n"
		"	sub     	%%esp, %%ecx		\n"
		"	shr     	$2, %%ecx			\n"
		"	rep stosl						\n"

		:									// outputs
		:									// inputs
		:	"eax", "ecx", "edi"				// clobbers
	);

	return x + y + z;
	// need to return this to avoid unused variable warning,
	// and to keep local vars from being optimized out of existence
}

int main(void)
{
	int		r = fn();

	return r;
}
