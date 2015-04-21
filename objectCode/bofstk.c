// Demonstrates attack code on the stack.
//
// Once you're in the attack code, you won't see anything in the
// source window, but you can track execution in registers via
// the value of EIP.

// contains buffer that is attacked by an "overflow"
void bofstk(int arg)
{
    int     buffer[4];

    // attack code instructions placed in buffer
    buffer[0] = 0x90909090;
    buffer[1] = 0xADBEEFB8;
    buffer[2] = 0x909090DE;

    // simulates an overflow:
    // return address on stack is hit with
    // address that is within the attack code
    buffer[5] = (int) &buffer[0];
}

int main(int argc, char **argv)
{
    bofstk(0xCAFEDEAD);

    return 0;
}
