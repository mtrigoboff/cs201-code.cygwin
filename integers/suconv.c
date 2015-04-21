// demonstrates that there's no data conversion when moving
// integer data between signed and unsigned variables

#include <stdio.h>

#define FIELD_WIDTH     8

int main (int argc, char **argv)
{
    int             s = -38;
    unsigned int    u = s;         // same bits, no data conversion

    printf("               u          s\n");
    printf("          ---------- ----------\n");
    printf("hex:      0x%0*X 0x%0*X\n", FIELD_WIDTH, u, FIELD_WIDTH, s);
    printf("signed:   %*d %*d\n", FIELD_WIDTH + 2, u, FIELD_WIDTH + 2, s);
    printf("unsigned: %*u %*u\n", FIELD_WIDTH + 2, u, FIELD_WIDTH + 2, s);
    return 0;
}
