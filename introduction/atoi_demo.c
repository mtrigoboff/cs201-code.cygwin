#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int		n;

	if (argc >= 2) {
		n = atoi(argv[1]);
		printf("n = %d\n", n);
		}
	else
		printf("no args\n");
}
