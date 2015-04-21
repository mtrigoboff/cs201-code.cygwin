// compile with optimization flag -O3
// and you will see some very smart optimization

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int     x = 2;
    int     y = 3;
    int     val;

    if (argc >= 3) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
        }

    // actually computes val = (3 * x) + 7
    val = x + y;
    val += x + 2;
    val += x - y;
    val += 5;

    printf("val = %d\n", val);
    return val;
}
