#include <stdio.h>
#include <stdbool.h>

void eatLine()
{
	while (getchar() != '\n') ;
}

int main(int argc, char** argv)
{
	int		i;
	short	s;
	int		nParsed;

	printf("type a 4-byte hex value to the %% prompt -- type 0 to end\n");
	while (true) {
		printf("%% ");
		nParsed = scanf("%x", &i);
		if (nParsed == 1)
			if (i == 0)
				break;
			else {
				s = i;
				printf("%X -> %hX\n", i, s);
				}
		else {
			eatLine();
			printf("bad input\n");
			}
		}

	return 0;
}
