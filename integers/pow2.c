// demonstrates the problem described in Bryant & O'Hallaron,
// section 2.3.7.  Using right-shift for division has a problem
// when the number being divided is negative.  This code
// prints out a table that shows the difference between the
// results of right-shift and division.

#include <stdio.h>
#include <stdlib.h>

void shift (int n, int exp2, int divisor)
{
    int     x;
    int     shifted;
    int     quotient;
    
    x = n;
    shifted = x >> exp2;
    quotient = x / divisor;
    printf("%4d >> %d = %4d     %4d / %d = %4d\n", n, exp2, shifted, n, divisor, quotient);
}

int main (int argc, char **argv)
{
    int     exp2 = 2;
    int     limit = -33;
    int     limitCmdLine;
    int     divisor;
    int     i;
    
    printf("\n   shift right            divide \n");
    printf(  "   -----------            ------ \n\n");
    
    if (argc > 1)
        exp2 = atoi(argv[1]);           // how many bits to shift
    if (argc > 2) {
        limitCmdLine = atoi(argv[2]);
        if (limitCmdLine > 1)
            limit = -limitCmdLine;      // how many lines to print
        }
    
    divisor = 1 << exp2;                // computes 2^exp2
    for (i = -1; i >= limit; i--)
        shift(i, exp2, divisor);

    printf("\n");
    return 0;
}
