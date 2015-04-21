// compilation of an if statement

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <stdlib.h>

int main (int argc, char **argv)
{
    int     x = argc > 1 ? atoi(argv[1]) : 2;
	int		y = -1;
    
    if (x <= 0)
        y = 0;
    else if (x == 1)
        y = 1;
    else if (x == 2)
        y = 2;
    else
        y = 3;

    return 0;
}
