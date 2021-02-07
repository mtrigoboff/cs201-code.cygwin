// demonstrates how integer arithmetic compiles

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main (int argc, char **argv)
{
    int     x = 3;
    int     y = 2;
    int     z = 4;
    int     val;
    
    val = (x + y) * z;

    return 0;
}
