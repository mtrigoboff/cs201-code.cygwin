// how to extract a bit field from a larger value,
// and how to insert a bit field into a larger value.
//
// optional arguments: x, insert

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    short       x = 0x1234;
    short       extracted;
    short       insert = 1;
	short		mask = 0x0018;

    if (argc >= 2)                  // did user provide an argument?
        x = atoi(argv[1]);          // use argument as value of x
    if (argc >= 3) {                // did user provide an argument?
        insert = atoi(argv[2]);     // use argument as value of insert
        insert &= 0x0003;           // mask out all but rightmost 2 bits
        }
    printf("(bits are counted from the right, starting with zero)\n\n");
    printf("x = 0x%04hX\n\n", x);

    // extract bit field from larger value
    printf("extracting bits 3-4\n");
    extracted = x & mask;			// mask out the bits we don't want
    extracted >>= 3;                // shift the bits we want to right end
    printf("extracted %d\n\n", extracted);

    // insert bit field into larger value
    printf("inserting %d into bits 3-4\n", insert);
    x &= ~mask;						// zero bits 3-4, no change to rest
    x |= insert << 3;               // insert new value into bits 3-4
    printf("x = 0x%04hX\n\n", x);

    return 0;
}
