// demonstrates "old mechanism" floating point comparison,
// including how NaN values are handled

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    double      x;
    double      y;
    
    if (argc >= 2) {
        x = atof(argv[1]);
        y = atof(argv[2]);
        }
    else
        x = y = 0.0;
    
    // set up demonstration of unordered result
    if (x == 0.0 && y == 0.0)
        x = 0.0/0.0;            // this is a NaN
    
    if (x < y)
        printf("x < y\n");
    else if (x > y)
        printf("x > y\n");
    else if (x == y)
        printf("x == y\n");
    else
        printf("unordered\n");
    
    return 0;
}
