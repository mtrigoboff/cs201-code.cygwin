#include <stdio.h>
#include <string.h>

static void eatLine ()
{
    while (getchar() != '\n') ;
}

int main(int argc, char** argv)
{
	char	str[16];
	float	f;
	int		nParsed;

	if (argc > 1 && strcmp(argv[1], "-help") == 0) {
		printf("Type hex to see equivalent float.\n");
		printf("Type float to see equivalent hex.\n");
		printf("Type a zero value of either kind to exit.\n\n");
		return 1;
		}
	for (;;) {
		printf(": ");
		scanf("%15s", str);
		if (str[0] == '0' && str[1] == 'x') {
			nParsed = sscanf(&str[2], "%X", (unsigned int *) &f);
			if (nParsed != 1) {
				eatLine();
				printf("bad hex input!\n\n");
				continue;
				}
			printf("= %.3f\n\n", f);
			}
		else {
			nParsed = sscanf(str, "%f", &f);
			if (nParsed != 1) {
				eatLine();
				printf("bad numeric input!\n\n");
				continue;
				}
			printf("= 0x%08X\n\n", *((unsigned int *) &f));
			}
		if (f == 0.0)
			break;
		}

	return 0;
}
