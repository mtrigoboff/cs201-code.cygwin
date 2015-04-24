// watch this code in insight and observe how the recursive
// function sumOf uses the program stack

// compute sum of n + (n - 1) + (n - 2) ... 1 recursively

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int sumOf(int n)
{
    if (n == 1)
        return 1;
    else
        return n + sumOf(n - 1);
}

int main(int argc, char **argv)
{
    int     x = 0;
    
    x = sumOf(3);
    
    return 0;
}
