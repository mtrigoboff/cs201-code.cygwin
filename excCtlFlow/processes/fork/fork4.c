// demonstrates a child that terminates normally,
// and a parent that doesn't wait for the child,
// but that can still reap the child if it waits until the child terminates

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork()
#include <sys/types.h>      // for pid_t
#include <sys/wait.h>       // for waitpid()

#define CHILD_WAIT      3

int main (int argc, char **argv)
{
    pid_t   pid;
    int     status;
    int     childRetVal = 123;
    int     parentWait = 3;     // seconds

    if (argc > 1)
        // get parent wait time from command line
        parentWait = atoi(argv[1]);
    pid = fork();
    if (pid < 0) {
        printf("fork error %d\n", pid);
        return -1;
        }
    else if (pid == 0) {
        // code that runs in the child process
        printf("child sleeps for %d sec\n", CHILD_WAIT);
        sleep(CHILD_WAIT);      // seconds
        printf("child returns %d\n", childRetVal);
        return childRetVal;
        }
    else {
        // code that runs in the parent process
        printf("parent sleeps for %d sec\n", parentWait);
        sleep(parentWait);      // seconds
        printf("parent calls waitpid\n");
        if (waitpid(pid, &status, WNOHANG) > 0) {
            printf("parent reaps child status 0x%08X\n", status);
            if (WIFEXITED(status))
                printf("child exited normally with %d\n", WEXITSTATUS(status));
            }
        printf("parent exits\n");
        return 0;
        }
}
