// demonstrates the use of a string operation (stosb)
// to store '+' into each element of an array of chars

int main(void)
{
	char	ar[] = {'a', 'b', 'c', 'd', 'e'};
	int		lgth = sizeof(ar) / sizeof(char);
    
    // fill array with new character
	asm("	cld								\n"		// set to increment
		"	lea     	%[ar], %%edi		\n"
		"	mov     	$'+', %%al			\n"
		"	mov     	%[lgth], %%ecx		\n"
		"	rep stosb						\n"

		:	[ar]		"=m"	(ar)		// outputs
		:	[lgth]		"m"		(lgth)		// inputs
		:	"ecx", "edi"					// clobbers
	);

	return 0;
}
