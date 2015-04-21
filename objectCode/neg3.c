#include <stdio.h>

// demonstrates three different ways to generate
// the negative of a two's complement integer value
int main (void)
{
    int     x = 3;

    printf("x = %d\n", x);

    // negative via sign
    x = -x;
    printf("x = %d\n", x);

    // negative via multiplication
    x *= -1;
    printf("x = %d\n", x);

    // negative by flipping all bits and then adding 1
    x = ~x;
    x += 1;
    printf("x = %d\n", x);

    return 0;
}

