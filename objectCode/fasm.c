// illustrates use of gcc's inline assembler
// with floating point values

#include <stdio.h>
#include <stdlib.h>

// add two numbers, return sum.
// Use of sum variable adds inefficiency:
// the assembly code stores value from ST(0) to sum,
// then the return code loads the value from sum
// back into ST(0).
double add1 (double x, double y)
{
    double  sum;

    asm(                                // contents of fp stack:
        "   fldl    %[x]        \n"     // x ...
        "   fldl    %[y]        \n"     // y x ...
        "   faddp               \n"     // sum ...
        "   fstpl   %[sum]      \n"     // ...

        :   [sum]   "=m"    (sum)       // outputs
        :   [x]     "m"     (x),        // inputs
            [y]     "m"     (y)
    );

    return sum;
}

// can be called with 2 command line arguments which will
// then be interpreted as floating point numbers and added
int main (int argc, char **argv)
{
    double  x = 1;
    double  y = 2;
    double  sum;

    if (argc == 3) {
        x = atof(argv[1]);
        y = atof(argv[2]);
        }

    sum = add1(x, y);
    printf("%.2f = add1(%.2f, %.2f)\n", sum, x, y);

    return 0;
}
