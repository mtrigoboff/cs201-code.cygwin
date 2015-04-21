// demonstrates the difference between signed and unsigned
// numbers when they are right-shifted

#include <stdio.h>

int main (int argc, char **argv)
{
    signed int      s = 0x81234567;
    unsigned int    u = 0x81234567;
    
    printf("s = 0x%08X, u = 0x%08X\n", s, u);
    s >>= 4;
    u >>= 4;
    printf("(right shift both by 4)\n");
    printf("s = 0x%08X, u = 0x%08X\n", s, u);

    return 0;
}
