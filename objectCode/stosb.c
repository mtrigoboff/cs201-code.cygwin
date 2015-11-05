// demonstrates the use of a string operation (stosb)
// to store '+' into each element of an array of chars

int main(void)
{
	char	array[] = {'a', 'b', 'c', 'd', 'e'};
	int		lgth = sizeof(array) / sizeof(char);
    
    // fill array with new character
	asm("	cld								\n"		// set to increment
		"	lea     	%[array], %%edi		\n"
		"	mov     	$'+', %%al			\n"
		"	mov     	%[lgth], %%ecx		\n"
		"	rep stosb						\n"

		:	[array]		"=m"	(array)		// outputs
		:	[lgth]		"m"		(lgth)		// inputs
		:	"ecx", "edi"					// clobbers
	);

	return 0;
}
