// this code causes repeated calls to signalHandler, which is not what we want

#pragma GCC diagnostic ignored "-Wdiv-by-zero"

#include <signal.h>
#include <stdio.h>

int     nTimes = 0;

void signalHandler(int signal)
{
    printf("signal %d received (%d)\n", signal, nTimes++);
}

int main()
{
    int     x;
    
    // set up signal handler
    if (signal(SIGFPE, signalHandler) == SIG_ERR)
        printf("signal error\n");

    printf("about to divide 1 by 0, type return when ready\n");
    getchar();
    
    x = 1 / 0;                  // divide by zero
    printf("x = %d\n", x);
    
    return 0;
}
