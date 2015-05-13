// demonstrates "memory aliasing" problem

#include <stdio.h>

void twiddle1 (int *xp, int *yp)
{
    *xp += *yp;
    *xp += *yp;
}

void twiddle2 (int *xp, int *yp)
{
    *xp += 2 * *yp;
}

int main ()
{
    int     x = 3;
    int     tw1, tw2;

    // twiddle1 and twiddle2 do the same thing
    tw1 = 3;
    twiddle1(&tw1, &x);
    tw2 = 3;
    twiddle2(&tw2, &x);
    printf("twiddle1 = %d, twiddle2 = %d\n", tw1, tw2);
    
    // or do they?
    tw1 = 3;
    twiddle1(&tw1, &tw1);
    tw2 = 3;
    twiddle2(&tw2, &tw2);
    printf("twiddle1 = %d, twiddle2 = %d\n", tw1, tw2);

    return 0;
}
 
