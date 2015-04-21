#include <stdio.h>
#include <stdlib.h>

void print (char *str, int x, float y)
{
    // print str, x and y on three separate lines
    printf("\nstr = \"%s\"\nx = %d\ny = %.1f\n\n", str, x, y);
}

int main (int argc, char **argv)
{
    int     x = -1;
    float   y;
    char    *str = "abcdefghijkl";
    			// this is different from  char str[] = "abcdefghijkl";
                // make sure you understand the difference!

    printf("\nCS200: Unix Programming Introduction\n\n");

    if (argc >= 2)          // if there is at least one command line argument
        str = argv[1];      // set str to point to the first argument
    if (argc >= 3)          // if there are at least two command line arguments
        x = atoi(argv[2]);  // set x to the value of the second argument

    // ask user to enter a value for y
    printf("enter a value for y > ");
    scanf("%f", &y);

    print(str, x, y);

    return 0;               // indicate successful run to Unix
}
