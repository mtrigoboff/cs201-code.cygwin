#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <stdio.h>

int main (int argc, char **argv)
{
    float     x = 3;
    float     y = 4;
    float     z;
    
    z = x + y;
    
	printf("z = %1.1f\n", z);
    return 0;
}
