// handle divide by zero fault competently

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

static int      numerator = 10;
static int      denominator = 0;
static int      err = 0;

void signalHandler(int signal)
{
    printf("signal %d received\n", signal);
    denominator = 1;        // stop error from happening again
    err = 1;                // record error
}

int main(int argc, char **argv)
{
    int     x;
    
    if (signal(SIGFPE, signalHandler) == SIG_ERR)
        printf("signal error\n");

    if (argc > 1)
        denominator = atoi(argv[1]);
    
    printf("about to divide %d by %d - hit return when ready",
		   numerator, denominator);
	getchar();
    x = numerator / denominator;
    if (! err)
        printf("x = %d\n", x);
    else
        printf("error occurred\n");
    
    return 0;
}
