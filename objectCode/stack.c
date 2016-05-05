// demonstrates the object code's use of the program stack.
// Run this code in insight and notice where the arguments
// and local variables are stored and how they are accessed.

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int fn(int x, int y, int z)
{
    int     m = 3;
    int     n;
    
    m = x;
    n = m + y;
    m = n + z;
    
    return m;
}

int main(int argc, char **argv)
{
    int     x;
    
    x = fn(5, 6, 7);
    
    return 0;
}
