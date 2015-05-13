// demonstrates "memory aliasing" problem

#include <stdio.h>

void swap (int *xp, int *yp)
{
    *xp = *xp + *yp;        // x = x + y
    *yp = *xp - *yp;        // y = (x + y) - y = x
    *xp = *xp - *yp;        // x = (x + y) - x = y
}

int main ()
{
    int     s1 = 3, s2 = 4;

    // swap works
    printf("s1 = %d, s2 = %d\n", s1, s2);
    swap(&s1, &s2);
    printf("s1 = %d, s2 = %d\n", s1, s2);
    
    // or does it?
    swap(&s1, &s1);
    printf("s1 = %d, s2 = %d\n", s1, s2);

    return 0;
}
