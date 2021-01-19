#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char** argv)
{
	if (strcmp(argv[0], "pa") != 0) {			// argv[0] != "pa"
		
		// detailed output

		printf("there are %d args\n", argc);
		for (int i = 0; i < argc; i++)
			printf("%d: \"%s\"\n", i, argv[i]);
		}

	else {
		
		// short output
		
		bool	first = true;

		for (int i = 0; i < argc; i++) {
			if (first)
				first = false;
			else
				printf(", ");
			printf("%s", argv[i]);
			}
		printf("\n");
		}
		
	return 0;
	}
