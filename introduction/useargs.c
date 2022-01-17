#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int         i;
    double      d;
    double      sum;
    
    if (argc != 3) {        // check that we have 2 arguments
        printf("provide 2 numeric arguments!\n");
        return -1;
        }
    
    i = atoi(argv[1]);
    d = atof(argv[2]);
    sum = i + d;
    printf("%d + %.2f = %.2f\n", i, d, sum);
    
    return 0;
}
