// demonstrates returning n levels above caller

#include <stdio.h>
#include <stdlib.h>

void fn(int depth, int skip)
{
    printf("fn(%d) called\n", depth);
    if (depth == 1) {
        printf("hit bottom\n");
        }
    else
        fn(depth - 1, skip);

    printf("fn(%d) returning\n", depth);

    if (depth == 1 && skip > 0) {
        printf("------------------\n");
        // follow stack frame pointer links to chosen stack frame,
        // then return from that stack frame to its caller
        asm("       mov     %[skip], %%ecx      \n"
            "next:  mov     (%%ebp), %%ebp      \n"
            "       loop    next                \n"
            "       mov     %%ebp, %%esp        \n"
            "       pop     %%ebp               \n"
            "       ret                         \n"
            :                                   // outputs
            :   [skip]  "m"     (skip)          // inputs
            :   "esp", "ecx"                    // clobbers (can't list ebp)
        );
        }
}

int main(int argc, char **argv)
{
    int     skip = 0;
    int     depth = 5;

    if (argc >= 2)
        skip = atoi(argv[1]);
    if (argc >= 3)
        depth = atoi(argv[2]);
    if (depth < 0 || skip < 0 || depth <= skip) {
        printf("bad args\n");
        return -1;
        }
    printf("main: calling fn with depth == %d, skip == %d\n", depth, skip);
    fn(depth, skip);
    printf("main: fn(%d) returned\n", depth);

    return 0;
}
