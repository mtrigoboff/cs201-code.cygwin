#include <stdio.h>

/* Demonstrates how to use sscanf to read in a number with
 * error checking. The variable named 'trailing' is used to
 * capture the first trailing non-numeric character of input
 * like '123xyz'. For this input, n will be set to 123,
 * 'trailing' will be set to "x", and sscanf will return 2.
 */

int main(int argc, char** argv)
{
	int		n;
	char	trailing;

	if (argc < 2) {
		printf("no argument\n");
		return -1;
		}
	if (sscanf(argv[1], "%d %c", &n, &trailing) != 1) {
		printf("%s is not a number\n", argv[1]);
		return -2;
		}
	
	printf("%d is a number\n", n);
	return 0;
}
