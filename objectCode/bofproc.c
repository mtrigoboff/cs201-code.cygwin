// Demonstrates running an unauthorized OS command by altering
// the return address on the stack.

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#define TARGET  3

// a privileged command in the operating system
void osCmd()
{
    // move recognizable value into eax to prove that
    // the simulated attack has worked
    asm("       mov     $0xCAFEDEAD, %eax       ");
}

// attack code
void bofproc(int arg)
{
    int     buffer[TARGET - 1];

    // buffer being filled with data that doesn't matter,
    // except that you will be able to recognize it as
    // you step through this code in insight
    buffer[0] = 0xDEBEADED;
    buffer[1] = 0xDEADBEEF;

    // hit return address with address of privileged command
    buffer[TARGET] = (int) osCmd;
}

int main(int argc, char **argv)
{
    bofproc(0xCAFEDEAD);

    return 0;
}
