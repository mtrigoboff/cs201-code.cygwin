// burn up time uselessly

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv)
{
    long long int   x = 1;
    long long int   i;
    long long int   n = argc > 1 ? atoll(argv[1]) : 3;       
                    // if arg[1] is present, use it as loop counter limit
    
    // burn up time
    for (i = 0; i < n; i++)
        x *= i;     

    printf("looped %lld times\n", n);
    return 0;
}
