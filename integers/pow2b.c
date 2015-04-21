// demonstrates both the wrong and the right ways of
// using right-shift to mimic division by a power of 2

#include <stdio.h>

void shift (int n, int pow2)
{
    int     x;

    printf("shifting %d left and right by %d bits\n", n, pow2);
    printf("                    %5d 0x%08X\n", n, n);

    x = n;
    x <<= pow2;
    printf("shift left:         %5d 0x%08X\n", x, x);

    x = n;
    x >>= pow2;
    printf("shift right:        %5d 0x%08X\n", x, x);

    if (n < 0) {
        x = n;
        x += (1 << pow2) - 1;   // add the "bias" before shifting
        x >>= pow2;
        printf("biased shift right: %5d 0x%08X\n", x, x);
        }

    printf("\n");
}

// divides x by 2^k, using a right shift and the "bias" method
// described in the textbook
void div2 (int x, int k)
{
    printf("biased divide: %4d / 2^%d is: %d\n\n",
           x, k, (x < 0 ? (x + ((1 << k) - 1)) : x) >> k);
}

int main (int argc, char **argv)
{
    shift(13, 1);
    shift(-13, 1);

    shift(14, 1);
    shift(-14, 1);

    shift(15, 1);
    shift(-15, 1);

    shift(16, 1);
    shift(-16, 1);

    shift(13, 2);
    shift(-13, 2);

    div2(13, 1);
    div2(-13, 1);

    div2(13, 2);
    div2(-13, 2);

    return 0;
}
