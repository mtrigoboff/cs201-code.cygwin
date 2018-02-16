// use with insight to demonstrate
// how argc and argv are stored on the stack

#pragma GCC diagnostic ignored "-Wunused-variable"

int main(int argc, char **argv)
{
    int     i = argc;
    char    *c = argv[0];
    
    return 0;
}
