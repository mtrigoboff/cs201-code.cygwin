// demonstrates how integer arithmetic compiles

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main (int argc, char **argv)
{
    int     x = 3;
    int     y = 2;
    int     val;
    
    // addition
    val = x + y;
    val = x + y + 1;

    // subtraction
    val = x - y;
    val = x - y - 1;
    
    return 0;
}
