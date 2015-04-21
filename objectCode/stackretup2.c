// demonstrates returning from caller's caller

#include <stdio.h>
#include <stdlib.h>

void three(int arg)
{
    printf("three called\n");
    printf("three returning to caller's caller\n");
    asm("       mov     (%ebp), %ebp        \n"     // caller's stack frame
        "       mov     %ebp, %esp          \n"     // stack ready for caller to return
        "       pop     %ebp                \n"     // caller's caller's stack frame
        "       ret                         \n"
    );
}

void two(int arg)
{
    printf("two called\n");
    three(0x33333333);
    printf("two returning\n");
}

void one(int arg)
{
    printf("one called\n");
    two(0x22222222);
    printf("one returning\n");
}

int main(void)
{
    printf("main: calling one()\n");
    one(0x11111111);
    printf("main: one() returned\n");

    return 0;
}
