#include <stdio.h>
#include <stdbool.h>

bool getValue(char *str, char *valuePtr)
{
	int		n;
	int		val;
	char	nextChar = '\0';

	n = sscanf(str, "%x %c", &val, &nextChar);
	if (n != 0 && nextChar == '\0') {
		*valuePtr = val;
		return true;
		}
	else
		return false;
}

void printResult(char x, char op, char y, char z)
{
	printf("%02X %c %02X = %02X\n", x & 0xFF, op, y & 0xFF, z & 0xFF);
}

int main(int argc, char **argv)
{
	char	x, y;

	if (argc < 3) {
		printf("requires 2 hex byte arguments\n");
		return -1;
		}
	if (! getValue(argv[1], &x)) {
		printf("argv[1] is not a hex value\n");
		return -2;
		}
	if (! getValue(argv[2], &y)) {
		printf("argv[2] is not a hex value\n");
		return -3;
		}

	printResult(x, '&', y, x & y);
	printResult(x, '|', y, x | y);

	return 0;
}
