int main (int argc, char **argv)
{
    asm("       mov     $0, %eax        \n"     // count number of times inner loop executes
        "       mov     $2, %ecx        \n"     // initialize outer loop counter
        "outer: push    %ecx            \n"     // preserve outer loop counter on stack
        "       mov     $3, %ecx        \n"     // initialize inner loop counter
        "inner: inc     %eax            \n"     // execution of inner loop
        "       loop    inner           \n"
        "       pop     %ecx            \n"     // restore outer loop counter from stack
        "       loop    outer           \n"
    );

    return 0;
}
