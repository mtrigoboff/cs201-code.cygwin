// divide by zero floating point error doesn't occur,
// even though there is a a defined floating point divide exception
// in the x87 FPU Control Word (IA-32 Manual, Volume 1, page 8-9)

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

static double   numerator = 1;
static double   denominator = 1;
static int      err = 0;

void signalHandler(int signal)
{
    printf("signal %d received\n", signal);
    denominator = 1.0;      // stop error from happening again
    err = 1;                // record error
}

int main(int argc, char **argv)
{
    double      x;
    
    if (signal(SIGFPE, signalHandler) == SIG_ERR)
        printf("signal error\n");

    // get denominator from user, if arg is present
    if (argc > 1)
        denominator = atof(argv[1]);
    
    printf("about to divide %.2f by %.2f\n", numerator, denominator);
    x = numerator / denominator;
    if (! err)
        printf("x = %.2f\n", x);
    else
        printf("error occurred\n");
    
    return 0;
}
