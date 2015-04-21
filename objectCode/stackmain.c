// use with insight to demonstrate
// how argc and argv are stored on the stack

#include <stdio.h>

int main(int argc, char **argv)
{
    char    *arg;
    int     i;
    
    for (i = 0; i < argc; i++) {
        arg = argv[i];
        printf("arg[%d] = \"%s\"\n", i, arg);
        }
    
    return 0;
}
