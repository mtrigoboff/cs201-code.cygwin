int main (int argc, char **argv)
{
    asm("       mov     $0, %eax        \n"
        "       mov     $4, %ecx        \n"
        "next:  add     $2, %eax        \n"
        "       loop    next            \n"
    );

    return 0;
}
