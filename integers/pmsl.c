// Patriot missile example from B&O'H, Practice Problem 2.32.
// For a given fraction, prints the following:
//   the bit representation of the fractional binary number
//   calcValue: the floating point value for the fraction
//   bitsValue: the actual value of the fractional binary representation
//   error:   the difference between the "real" value and the fractional binary value
//            (this prints in two formats, as a decimal number and in scientific notation)

#include <stdlib.h>
#include <stdio.h>

#define WIDTH       12
#define PRECISION    8

static char     helpStr[] = "call with 3 args: nBits numerator denominator";

int main (int argc, char **argv)

{
    int     nBits;
    int     numerator;
    int     denominator;
    double  error;          // difference between fractional binary value and floating point value
    int     b;

    if (argc != 4) {
        printf("%s\n", helpStr);
        return -1;
        }

    nBits = atoi(argv[1]);
    numerator = atoi(argv[2]);
    denominator = atoi(argv[3]);

    if (nBits <= 0 || numerator <= 0 || denominator <= 0 ||  numerator >= denominator) {
        printf("bad arguments\n");
        return -2;
        }

	{
    double  calcValue;			// floating point calculated value of fraction
    double  bitsValue = 0;		// numeric value of the fractional binary representation
	double  oneHalf = 0.5;
    double  p2 = oneHalf;		// current power of 1/2 we're using

    calcValue = ((double) numerator) / (double) denominator;
    error = calcValue;
    printf("\nnumerator:     %d\n", numerator);
    printf("denominator:   %d\n", denominator);
    printf("\n%02d bit value:  0.", nBits);
    
    // compute fractional binary value by adding powers of 1/2 as needed,
    // simultaneously print out the fractional binary value
    for (b = 0; b < nBits; b++) {
        if (p2 <= error) {
            bitsValue += p2;	// continue computation of fractional binary value
            error -= p2;        // continue computation of error
            printf("1");
            }
        else
            printf("0");
        p2 *= oneHalf;          // next power of 1/2
        }
    printf("\n\ncalcValue:   %*.*f\n", WIDTH, PRECISION, calcValue);
    printf(    "bitsValue:   %*.*f\n", WIDTH, PRECISION, bitsValue);
    printf(    "error:       %*.*f\n", WIDTH, PRECISION, error);
    printf(    "             %*.*e\n", WIDTH, PRECISION - 4, error);
	}

    printf("\n");
    return 0;
}
