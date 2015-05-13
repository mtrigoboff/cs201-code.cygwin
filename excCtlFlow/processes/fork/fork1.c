// demonstrates a parent that waits for a child that terminates normally

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork()
#include <sys/types.h>      // for pid_t
#include <sys/wait.h>       // for waitpid()

int main (int argc, char **argv)
{
    pid_t   pid;
    int     status;
    int     childRetVal = 123;

    if (argc > 1)
        childRetVal = atoi(argv[1]);
    pid = fork();
    if (pid < 0) {
        printf("fork error %d\n", pid);
        return -1;
        }
    else if (pid == 0) {
        // code that runs in the child process
        printf("child returns %d\n", childRetVal);
        return childRetVal;
        }
    else {
        // code that runs in the parent process
        printf("parent waiting\n");
        if (waitpid(pid, &status, 0) > 0) {
            printf("parent reaps child status 0x%08X\n", status);
            if (WIFEXITED(status))
                printf("child exited normally with %d\n", WEXITSTATUS(status));
            }
        return 0;
        }
}
