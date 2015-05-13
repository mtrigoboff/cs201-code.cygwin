// this code is based on problem 8.18 and the code in figure 8.36
//
// demonstrates child signaling its parent,
// and parent USUALLY (but not always) counting those signals
// (the child will sleep between sending signals if there are no
//  command-line arguments, but will not sleep if there is at least one)

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static int      counter = 0;

void signalHandler (int signal)
{
    counter++;
    printf("signal %d, counter = %d\n", signal, counter);
}

int main (int argc, char **argv)
{
    if (fork() == 0) {                  // child
        int     ppid = getppid();
        int     i;

        sleep(3);                       // let parent run first to set up signal handler
            // This currently works on this particular machine. On a different machine,
            // or on this machine with an updated version of the operating system, it might
            // not be long enough. This is an OK thing to do for demo code, but it is
            // definitely not "industrial strength."

        printf("child will %swait between signals\n",
                argc <= 1 ? "" : "not ");
        for (i = 0; i < 5; i++) {
            kill(ppid, SIGUSR2);
            printf("child sends SIGUSR2 to parent\n");
            if (argc <= 1)
                sleep(1);
            }
        printf("child exits with counter = %d\n", counter);
        return 1;
        }
    else {                              // parent
        int     status;
        
        // set up signal handler, only needed in parent
        if (signal(SIGUSR2, signalHandler) == SIG_ERR) {
            printf("signal error\n");
            return 1;
            }

        if (wait(&status) > 0) {        // simpler form of waitpid()
            if (WIFEXITED(status))
                printf("child exited normally, returned %d\n", WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                printf("child exited with uncaught signal %d\n",
                        WTERMSIG(status));
            }
        printf("parent exits with counter = %d\n", counter);
        return 0;
        }
}
