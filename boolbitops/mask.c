// how to extract a bit field from a larger value,
// and how to insert a bit field into a larger value.
//
// optional arguments: x, insert

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    short       x = 0x1228;
    short       extracted;
	short		newBits;
	short		mask = 0x0018;

    if (argc >= 2)                  // did user provide an argument?
        x = atoi(argv[1]);          // use argument as value of x

    // extract bit field from larger value
    extracted = x & mask;			// mask out the bits we don't want
    extracted >>= 3;                // shift the bits we want to right end

	newBits = extracted + 1;		// add one to extracted bits
    newBits <<= 3;					// line new value up to bits 3-4
	newBits &= mask;				// only keep bits 3-4

    // insert bit field into larger value
    mask = ~mask;					// create inverted mask
    x &= mask;						// zero bits 3-4, no change to rest
	x |= newBits;                   // insert new value into bits 3-4

    return 0;
}
