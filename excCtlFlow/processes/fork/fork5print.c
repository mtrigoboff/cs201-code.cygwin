// demonstrates multiple children

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork()
#include <signal.h>         // for kill()
#include <sys/types.h>      // for pid_t
#include <sys/wait.h>       // for waitpid()

#define     N_TICK_PROCESSES    3

typedef struct {
    char    *ch;            // character to print
    char    *interval;      // seconds
    pid_t   pid;
    }
TickSpecifier;

TickSpecifier   ts[N_TICK_PROCESSES] = {{"+", "1", 0},
                                        {"-", "2", 0},
                                        {"!", "3", 0}
                                        };

int main (int argc, char **argv)
{
    int     status;
    pid_t   pid;
    int     i;

    for (i = 0; i < N_TICK_PROCESSES; i++) {
        pid = fork();
        if (pid == 0)
            execl("tick", "tick", ts[i].ch, ts[i].interval, (char *) 0);
                // execl never returns
                // the first argument would be "tick.exe" in Cygwin
        else {
            ts[i].pid = pid;    // might be < 0 if fork() error
            printf("forked pid %d with ch '%s' and interval %s\n",
                    pid, ts[i].ch, ts[i].interval);
            }
        }

    printf("parent %d waiting\n\n", getpid());

    getchar();		// wait for user to type a return

    // kill the children
    printf("\n");
    for (i = 0; i < N_TICK_PROCESSES; i++) {
        printf("killing %d with signal %d\n", ts[i].pid, SIGKILL);
        pid = ts[i].pid;
        if (pid > 0) {
            kill(pid, SIGKILL);
            if (waitpid(pid, &status, 0) > 0) {
                printf("  reaped with ");
                if (WIFEXITED(status))
                    printf("status %d\n", WEXITSTATUS(status));
                else if (WIFSIGNALED(status))
                    printf("uncaught signal %d\n", WTERMSIG(status));
                }
            }
        }

    return 0;
}
