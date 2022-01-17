// demonstrates the C boolean bitwise operations

#include <stdio.h>

int main (int argc, char **argv)
{
    short       x = 0x010F;
    short       y = 0x0F00;
    short       v;

    printf("C boolean Bitwise Ops\n");
    printf("---------------------\n");
    printf("           x = 0x%04hX\n", x);
    printf("           y = 0x%04hX\n", y);
    
    // not
    v = ~x;
    printf("not:      ~x = 0x%04hX\n", v);
    
    // or
    v = x | y;
    printf("or:    x | y = 0x%04hX\n", v);
    
    // and
    v = x & y;
    printf("and:   x & y = 0x%04hX\n", v);
    
    // exclusive or (xor)
    v = x ^ y;
    printf("xor:   x ^ y = 0x%04hX\n", v);
    
    return 0;
}
