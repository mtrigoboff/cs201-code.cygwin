#include <stdio.h>

#define WIDTH       40
#define PRECISION   38

// this function gets the value of pi from the FPU
double pi ()
{
    double dpi;

    // get value of pi from the CPU
    asm("       fldpi           \n"     // load pi to ST(0)
        "       fstpl   %[dpi]  \n"     // store ST(0) to dpi
        :   [dpi]   "=m"    (dpi)       // output
    );

    return dpi;
}

int main (void)
{
    printf("pi = %16.14f\n", pi());

    return 0;
}

