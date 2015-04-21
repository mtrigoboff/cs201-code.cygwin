// Patriot missile example from B&O'H, Practice Problem 2.32.
// For a given fraction, prints the following:
//   the bit representation of the fractional binary number
//   fpValue: the floating point value for the fraction
//   fbValue: the actual value of the fractional binary representation
//   error:   the difference between the "real" value and the fractional binary value
//            (this prints in two formats, as a decimal number and in scientific notation)

#include <stdlib.h>
#include <stdio.h>

#define WIDTH       70
#define PRECISION   60

static char     helpStr[] = "call with 3 args: nBits numerator denominator";
static double   oneHalf = 0.5;

int main (int argc, char **argv)
{
    int     nBits;
    int     numerator;
    int     denominator;
    double  fpValue;        // floating point calculated value of fraction
    double  error;          // difference between fractional binary value and floating point value
    double  p2 = oneHalf;   // current power of 1/2 we're using
    double  fbValue = 0;    // numeric value of the fractional binary representation
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

    fpValue = ((double) numerator) / (double) denominator;
    error = fpValue;
    printf("\nnumerator = %d, denominator = %d\n", numerator, denominator);
    printf("\n%d bit value:    0.", nBits);
    
    // compute fractional binary value by adding powers of 1/2 as needed,
    // simultaneously print out the fractional binary value
    for (b = 0; b < nBits; b++) {
        if (p2 <= error) {
            fbValue += p2;      // continue computation of fractional binary value
            error -= p2;        // continue computation of error
            printf("1");
            }
        else
            printf("0");
        p2 *= oneHalf;          // next power of 1/2
        }
    printf("\n\nfpValue: %*.*f\n", WIDTH, PRECISION, fpValue);
    printf(    "fbValue: %*.*f\n", WIDTH, PRECISION, fbValue);
    printf(    "error:   %*.*f\n", WIDTH, PRECISION, error);
    printf(    "         %*.*e\n", WIDTH, PRECISION - 4, error);

    printf("\n");
    return 0;
}
