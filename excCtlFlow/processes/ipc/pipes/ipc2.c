// attempts inter-process communication using a pipe

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork(), sleep(), pipe()
#include <sys/wait.h>       // for waitpid()

static char     line[256];
static int      comm[2];
static char     stopCmd = 'x';

int main ()
{
    pid_t   pid;
    int     status;

    // set up pipe
    if (pipe(comm)) {
        printf("pipe error\n");
        return -1;
        }

    // fork into parent and child processes
    pid = fork();

    // fork() failed
    if (pid < 0) {
        printf("fork error %d\n", pid);
        return -1;
        }

    // code that runs in the child process
    else if (pid == 0) {
        close(comm[1]);         // child doesn't need output side of pipe
        printf("child about to read from pipe\n");
        while (! read(comm[0], &stopCmd, 1)) {
            printf("%c", '.');
            fflush(stdout);     // override line buffering so we see single char output
            sleep(1);           // 1 second
            }
        printf("child reads '%c' from pipe\n", stopCmd);
        close(comm[0]);
        printf("child exits\n");
        return 210;
        }

    // code that runs in the parent process
    else {
        close(comm[0]);         // parent doesn't need input side of pipe
        printf("parent waiting\n");
        gets(line);
        write(comm[1], &stopCmd, 1);
        printf("parent tells child to stop\n");
        waitpid(pid, &status, 0);
        printf("parent reaps child status 0x%08X\n", status);
        if (WIFEXITED(status))
            printf("child exited normally with %d\n", WEXITSTATUS(status));
        close(comm[1]);
        printf("parent exits\n");
        return 0;
        }
}

