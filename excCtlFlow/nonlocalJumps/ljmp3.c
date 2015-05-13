// implementation of factorial that returns using longjmp

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

// computes factorial result "on the way down" the recursion
void fact2(int n, int result, jmp_buf jb)
{
    if (n <= 1)
        longjmp(jb, result);
    else
        fact2(n - 1, result * n, jb);
}

int fact(int n)
{
    jmp_buf     jb;
    int         sjVal;

    sjVal = setjmp(jb);     // why don't we need to use the & operator for jb?

    if (sjVal == 0) {       // we just called setjmp
        fact2(n, 1, jb);
        // the following return statement will never be executed because
        // fact2 does not return normally. But including this statement
        // avoids a compiler warning.
        return 0;
        }
    else                    // setjmp returned from a call to fact2
        return sjVal;
}

int main(int argc, char **argv)
{
    int     n = argc > 1 ? atoi(argv[1]) : -1;
    int     f;

    if (n < 0) {
        printf("one numeric argument is required\n");
        return -1;
        }

    f = fact(n);

    printf("fact(%u) = %6u\n", n, f);
    return 0;
}
