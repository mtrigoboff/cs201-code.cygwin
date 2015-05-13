// demonstrates a parent that waits for a child that dies and throws a signal

#pragma GCC diagnostic ignored "-Wdiv-by-zero"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork()
#include <sys/types.h>      // for pid_t
#include <sys/wait.h>       // for waitpid()

int main ()
{
    pid_t   pid;
    int     status;

    pid = fork();
    if (pid < 0) {
        printf("fork error %d\n", pid);
        return -1;
        }
    else if (pid == 0) {
        int     x;
        // code that runs in the child process
        printf("child about to divide by zero\n");
        x = 1 / 0;
        printf("child returning\n");
        return 123;
        }
    else {
        // code that runs in the parent process
        printf("parent waiting\n");
        if (waitpid(pid, &status, 0) > 0) {
            printf("parent reaps child status 0x%08X\n", status);
            if (WIFEXITED(status))
                printf("child exited normally with %d\n", WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                printf("child exited with uncaught signal %d\n", WTERMSIG(status));
            }
        return 0;
        }
}
