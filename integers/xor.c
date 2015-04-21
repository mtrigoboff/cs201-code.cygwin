// demonstrates the xor swapping trick.
// You will need to run this code in a debugger.

int main (int argc, char **argv)
{
    char    x = 0x0F;   // x = 00001111
    char    y = 0x01;   // y = 00000001
    
    x ^= y;             // x = 00001110
    y ^= x;             // y = 00001111
    x ^= y;             // x = 00000001

    return 0;
}
