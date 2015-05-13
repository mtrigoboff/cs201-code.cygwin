// handles divide by zero floating point error

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

static jmp_buf  jb;                             // buffer for setjmp, longjmp

void signalHandler(int signal)
{
    printf("signalHandler received signal %d\n", signal);
    longjmp(jb, signal == 0 ? -1 : signal);     // avoid returning zero via longjmp
}

int main(int argc, char **argv)
{
    double      numerator = 1.0;
    double      denominator = 1.0;
    double      quotient;
    short       fcw;                            // used to unmask fp exceptions
    int         sjVal;

    if (signal(SIGFPE, signalHandler) == SIG_ERR) {
        printf("signal error\n");
		return -1;
		}

    // set fp control word to unmask zero divide exception
    asm("   fstcw   %[fcwOut]           \n"     // get fp control word
        "   andw    $0xFFFB, %[fcwIn]   \n"     // unmask zero divide exception
        "   fldcw   %[fcwIn]            \n"     // store fp control word
        : [fcwOut]     "=m"     (fcw)           // outputs
        : [fcwIn]      "m"      (fcw));         // inputs

    // get denominator from user, if arg is present
    if (argc > 1)
        denominator = atof(argv[1]);

    printf("about to divide %.2f by %.2f\n", numerator, denominator);
    sjVal = setjmp(jb);
    if (sjVal == 0) {               // we just called setjmp()
        quotient = numerator / denominator;     // perform the division
        printf("quotient = %.2f\n", quotient);  // print result, if we get here
        }
    else {                          // setjmp() returned from signalHandler()
        printf("zero divide error, signal %d\n", sjVal);
        }

    return 0;
}
