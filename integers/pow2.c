// demonstrates the problem described in Bryant & O'Hallaron,
// section 2.3.7.  Using right-shift for division has a problem
// when the number being divided is negative.  This code
// prints out data that shows the difference between the
// results of right-shift and division.

#include <stdio.h>
#include <stdlib.h>

void shift (short n, short exp2, short divisor)
{
    short   shifted =  n >> exp2;
    short   quotient = n / divisor;

    printf("%3d >> %d = %2d     %3d / %d = %2d\n", n, exp2, shifted, n, divisor, quotient);
}

int main (int argc, char **argv)
{
    short	exp2 = 2;
    short   limit = -15;
    short   limitCmdLine;
    short   divisor;
    short   i;
    
    printf("\n shift right         divide\n");
    printf(  "-------------     ------------\n");
    
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
