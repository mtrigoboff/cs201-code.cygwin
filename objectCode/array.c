#include <stdio.h>

// adds up elements of the array using an index

int main (int argc, char **argv)
{
    int     array[] = {1, 2, 3, 4};
    int     sum = 0;
    int     i;
    
    for (i = 0; i < sizeof(array) / sizeof(int); i++)
        sum += array[i];
    
    printf("sum = %d\n", sum);
    return 0;
}
