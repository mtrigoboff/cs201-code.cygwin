#include <stdlib.h>

int main()
{
	char*	mem_ptr = malloc(8);
	char*	ch_ptr = mem_ptr;
	char	ch = 'a';

	for (int i = 0; i < 8; i++, ch++, ch_ptr++)
		*ch_ptr = ch;

	free(mem_ptr);
}
