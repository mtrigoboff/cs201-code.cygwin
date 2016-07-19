#include <stdio.h>

// adds up elements of the array using a pointer

int main (int argc, char **argv)
{
    int     ar[] = {1, 2, 3, 4};
    int     sum = 0;
    int     *p;
    
    for (p = ar; p < &ar[sizeof(ar)/sizeof(int)]; p++)
        sum += *p;
    
    printf("sum = %d\n", sum);
    return 0;
}
