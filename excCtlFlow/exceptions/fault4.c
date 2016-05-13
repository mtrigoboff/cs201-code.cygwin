// handles divide by zero floating point error

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

static double   numerator = 1.0;
static double   denominator = 1.0;
static int      err = 0;
static int      nTimes = 0;

void signalHandler(int signal)
{
    printf("signalHandler received signal %d (%d)\n", signal, nTimes++);
    err = 1;
    denominator = 1.0;
    return;                                     // needed to turn off compiler warning
}

int main(int argc, char **argv)
{
    double      quotient;
    short       fcw;                            // used to unmask fp exceptions

    if (signal(SIGFPE, signalHandler) == SIG_ERR)
        printf("signal error\n");

    // set fp control word to unmask zero divide exception
    asm("   fstcw   %[fcwOut]           \n"     // get fp control word
        "   andw    $0xFFFB, %[fcwIn]   \n"     // unmask zero divide exception
        "   fldcw   %[fcwIn]            \n"     // store fp control word
        : [fcwOut]     "=m"     (fcw)           // outputs
        : [fcwIn]      "m"      (fcw));         // inputs

    // get denominator from user, if arg is present
    if (argc > 1)
        denominator = atof(argv[1]);

    printf("about to divide %.2f by %.2f - hit return when ready",
		   numerator, denominator);
	getchar();
    quotient = numerator / denominator;     // perform the division
    if (! err)
        printf("quotient = %.2f\n", quotient);  // print result, if we get here
    else
        printf("error occurred\n");

    return 0;
}
