// attempts inter-process communication using a global variable

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork(), sleep()
#include <sys/wait.h>       // for waitpid()

static int      stop = 0;
static char     line[256];
static char     ch = '+';

int main ()
{
    pid_t   pid;
    int     status;

    // fork into parent and child processes
    pid = fork();

    // fork() failed
    if (pid < 0) {
        printf("fork error %d\n", pid);
        return -1;
        }

    // code that runs in the child process
    else if (pid == 0) {
        // code that runs in the child process
        while (! stop) {
            printf("%c", ch);
            fflush(stdout);     // override line buffering so we see single char output
            sleep(1);           // 1 second
            }
        printf("child exits\n");
        return 0;
        }

    // code that runs in the parent process
    else {
        // code that runs in the parent process
        printf("parent waiting\n");
        gets(line);
        stop = 1;               // tell child to stop via global variable
        printf("parent tells child to stop\n");
        waitpid(pid, &status, 0);
        printf("parent reaps child status 0x%08X\n", status);
        if (WIFEXITED(status))
            printf("child exited normally with %d\n", WEXITSTATUS(status));
        printf("parent exits\n");
        return 0;
        }
}
