#include <stdio.h>

int main()
{
	char	cmd;

	for(;;) {
		printf("%% ");
		cmd = getchar();
		getchar();				// eat newline char
		switch (cmd) {
			case 'a': case 'A':
				printf("a!\n");
				break;
			case 'b': case 'B':
				printf("b!\n");
				break;
			case 'c': case 'C':
				printf("c!\n");
				break;
			case 'd': case 'D':
				printf("d!\n");
				break;
			case 'e': case 'E':
				printf("exiting...\n");
				goto exit;
			default:
				printf("?\n");
				break;
			}
		}
	
exit:
	return 0;
}
