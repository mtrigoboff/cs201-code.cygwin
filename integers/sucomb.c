// demonstrates what can happen when you combine
// signed and unsigned values in the same expression.
// Why does this code think that -1 is greater than 3?

#include <stdio.h>

int main (int argc, char **argv)
{
    int             s = -1;
    unsigned int    u = 3;

    printf("s = %d, u = %u\n", s, u);
    if (s < u)
        printf("s < u\n");
    else
        printf("s >= u\n");
    return 0;
}
