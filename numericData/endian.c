// demonstrates the endian byte ordering
// of the machine it's running on

#include <stdio.h>
#include <stdlib.h>

void printBytes (char *p, int nBytes)
{
    int     i;
    
    printf("bytes: ");
    for (i = 0; i < nBytes; i++, p++)
        printf("%02X", (unsigned char) *p);
    printf("\n");
}

int main (int arg, char **argv)
{
    unsigned int     n4 = 0xAABBCCDD;
    unsigned short   n2 = 0xAABB;

    printf("endian demo\n\n");
    
    printf("int:   %08X\n", n4);
    printBytes((char *) &n4, sizeof(n4));
    printf("\n");
    
    printf("short: %04X\n", n2);
    printBytes((char *) &n2, sizeof(n2));
    printf("\n");
    
    return 0;
}
