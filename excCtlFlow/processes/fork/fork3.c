// demonstrates a child that terminates normally,
// and a parent that doesn't wait for the child

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork() and sleep()
#include <sys/types.h>      // for pid_t
#include <sys/wait.h>       // for waitpid()

int main (int argc, char **argv)
{
    pid_t   pid;
    int     status;
    int     childRetVal = 123;
    int     napTime = 3;

    if (argc > 1)
        napTime = atoi(argv[1]);
    pid = fork();
    if (pid < 0) {
        printf("fork error %d\n", pid);
        return -1;
        }
    else if (pid == 0) {
        // code that runs in the child process
        printf("child about to sleep for %d second(s)\n", napTime);
        sleep(napTime);       // sleep for napTime seconds
        printf("child returns %d\n", childRetVal);
        return childRetVal;
        }
    else {
        // code that runs in the parent process
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
