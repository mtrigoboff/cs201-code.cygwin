// demonstrates both the wrong and the right ways of
// using right-shift to mimic division by a power of 2

#include <stdio.h>
#include <stdlib.h>

void shift (short n, short pow2)
{
    short	nBiased;

    printf("shifting %hd left and right by %hd bits\n", n, pow2);
    printf("shift left:       %5hd\n", n << pow2);
    printf("shift right:      %5hd\n", n >> pow2);

    if (n < 0) {
        nBiased = n + (1 << pow2) - 1;	// add the "bias" before shifting
        nBiased >>= pow2;
        printf("biased shift right: %3hd\n", nBiased);
        }

    printf("\n");
}

// divides n by 2^exp, using a right shift and
// the "bias" method described in the textbook
void div2 (int n, int exp)
{
    printf("biased divide: %4d / 2^%d is: %3d\n\n", n, exp,
		   (n < 0 ? (n + ((1 << exp) - 1)) : n) >> exp);
		   /* if n < 0
			*   n += (1 << exp) - 1
			* n >>= exp
			*/
}

int main (int argc, char **argv)
{
	if (argc < 3) {
		printf("need number to shift, power of 2 to shift by\n");
		exit(-1);
		}

	short	n =		atoi(argv[1]);
	short	pow2 =	atoi(argv[2]);

    shift(n, pow2);
    shift(-n, pow2);

    div2(n, pow2);
    div2(-n, pow2);

    return 0;
}
