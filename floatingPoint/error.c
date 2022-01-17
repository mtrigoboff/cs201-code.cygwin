#include <stdio.h>

#define WIDTH       40
#define PRECISION   38

void printHexBytes (unsigned char *p, int nBytes)
{
    int         i;
    
    printf("0x");
    for (i = 0, p = p + nBytes - 1; i < nBytes; i++, p--)
        printf("%02X", *p);
    printf("\n");
}

int main (void)
{
    float       fpi;
    double      dpi;
    
    // get value of pi from hardware
    asm("       fldpi                       \n" 
        "       fstpl       %[dpi]          \n"
        :   [dpi]   "=m"    (dpi)           // output
    );

    printf("double value of pi\n");
    printf("%*.*f\n", WIDTH, PRECISION, dpi);
    printHexBytes((unsigned char *) &dpi, sizeof(dpi));
    printf("\n");
    
    printf("float value of pi\n");
    fpi = dpi;
    printf("%*.*f\n", WIDTH, PRECISION, fpi);
    printHexBytes((unsigned char *) &fpi, sizeof(fpi));
    printf("\n");

    return 0;
}

