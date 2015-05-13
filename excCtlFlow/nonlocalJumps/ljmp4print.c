// this version does some extra printing to demonstrate what's happening

// implementation of factorial that returns using longjmp,
//   and only calls setjmp one time

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

static jmp_buf      jb;
static int          sjCalled = 0;

// computes factorial result "on the way down" the recursion
void fact2(int n, int result, jmp_buf jb)
{
    printf("fact2(%d, %d)\n", n, result);
    if (n <= 1) {
        printf("calling longjmp with %d\n", result);
        longjmp(jb, result);
        }
    else
        fact2(n - 1, result * n, jb);
}

int fact(int n)
{
    int         sjVal;

    if (sjCalled == 0) {
        sjCalled = 1;
        printf("calling setjmp\n");
        sjVal = setjmp(jb); // why don't we need to use the & operator for jb?
                            // (see /usr/include/setjmp.h)
        printf("returned from setjmp with %d\n", sjVal);
        }
    else
        sjVal = 0;          // so that fact2 will be called

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
