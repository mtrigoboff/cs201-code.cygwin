#include <stdio.h>
#include <stdlib.h>

#define PRECISION   14

// this function gets the value of pi from the FPU
double pi()
{
    double dpi;

    // get value of pi from the CPU
    asm("       fldpi           \n"     // load pi to ST(0)
        "       fstpl   %[dpi]  \n"     // store ST(0) to dpi
        :   [dpi]   "=m"    (dpi)       // output
    );

    return dpi;
}

int main(int argc, char** argv)
{
	int		precision = PRECISION;

	if (argc > 1) {
		precision = atoi(argv[1]);
		precision = precision == 0 ? PRECISION : precision;
		}

    printf("pi = %*.*f\n", precision + 2, precision, pi());

    return 0;
}

