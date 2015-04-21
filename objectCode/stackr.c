// watch this code in insight and observe how the recursive
// function sumOf uses the program stack

// compute sum of n + (n - 1) + (n - 2) ... 1 recursively

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int sumOf(int n)
{
    int     sum = 0;
    
    if (n == 1)
        sum = 1;
    else
        sum = n + sumOf(n - 1);
    
    return sum;
}

int main(int argc, char **argv)
{
    int     x = 0;
    
    x = sumOf(3);
    
    return 0;
}
