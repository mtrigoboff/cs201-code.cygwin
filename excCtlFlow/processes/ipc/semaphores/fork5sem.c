// demonstrates multiple children which will cooperate using
// a semaphore if a command-line argument is given
// (argument is number of processes that can simultaneously "grab"
//  the semaphore.  1 is a good argument to try with this code.)

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork()
#include <sys/wait.h>       // for waitpid()
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

typedef struct {
    char    ch;             // character to print
    int     interval;       // seconds
    int     nTimes;         // how many times to print ch
    int     retVal;         // value to return
    pid_t   pid;
    }
TickSpecifier;

TickSpecifier   ts[] = {{'+', 1, 4, 1, 0},
                        {'-', 1, 6, 2, 0},
                        {'!', 1, 8, 3, 0}};

#define N_TICK_PROCESSES	sizeof(ts)/sizeof(TickSpecifier)

static void semcall (int sid, int op)    /* call semop */
{
    struct sembuf sb;       // 1-element "array"
    sb.sem_num = 0;         // operate on the first (and only) semaphore
    sb.sem_op = op;         // number to add(subtract) to(from) semaphore value
    sb.sem_flg = SEM_UNDO;  // will be undone if this process terminates
    if (semop(sid, &sb, 1) == -1) {     // perform requested operation
        printf ("Error in semop\n");
        exit(-1);
        }
}

void initSem (int sid, int nAllowed)
{
    // initialize value of semaphore to nAllowed, which will allow
    // that many processes to acquire this semaphore at the same time
    semcall(sid, nAllowed);
}

void acquireSem (int sid)
{
    // value of semaphore must be > 0,
    // otherwise this will wait until it is restored to > 0
    // and then decrement it and acquire the semaphore
    // for the calling process
    semcall(sid, -1);
}

void releaseSem (int sid)
{
    // restore value of semaphore to > 0,
    // allowing some other process to acquire it
    semcall(sid, 1);
}
     
int main (int argc, char **argv)
{
    int     status;
    pid_t   pid;
    int     i;

    int     sid;
    int     nAllowed = 1;   // how many process at a time allowed in semaphore

    if (argc > 1)
        nAllowed = atoi(argv[1]);
    if (nAllowed < 1) {
        printf("invalid argument: %s - requires a number > 0\n", argv[1]);
        return 1;
        }

    // create the semaphore
    //
    // IPC_PRIVATE means create a new semaphore each time this runs.
    // Semaphores are "persistent", and this flag must be used to create
    // a unique new one.  "man semget" states that IPC_PRIVATE was an
    // unfortunate choice of name, and that IPC_NEW would have been better.
    if ((sid = semget(IPC_PRIVATE, 1, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
        printf ("couldn't get semaphore\n");
        exit(-1);
        }
    initSem(sid, nAllowed);
    printf("semaphore initial value: %d\n", nAllowed);

    for (i = 0; i < N_TICK_PROCESSES; i++) {
        pid = fork();
        if (pid == 0)
            goto child;
        else {
            ts[i].pid = pid;    // this might be < 0 if fork() error
            printf("forked pid %d with ch '%c', interval %d, nTimes %d\n",
                    pid, ts[i].ch, ts[i].interval, ts[i].nTimes);
            }
        }

    // report whether or not children are using the semaphore
    printf("children are %susing semaphore\n", argc > 1 ? "" : "not ");
    
    printf("parent %d waiting\n", getpid());
    getchar();
    for (i = 0; i < N_TICK_PROCESSES; i++) {
        printf("killing %d\n", ts[i].pid);
        pid = ts[i].pid;
        if (pid > 0) {
            kill(pid, SIGKILL);
            if (waitpid(pid, &status, WUNTRACED) > 0) {
                printf("parent reaps child %d status 0x%08X\n", pid, status);
                if (WIFEXITED(status))
                    printf("child exited normally with %d\n",
                            WEXITSTATUS(status));
                else if (WIFSIGNALED(status))
                    printf("child exited with uncaught signal %d\n",
                            WTERMSIG(status));
                }
            }
        }
    return 0;

child: {
    // code that runs in the child process
    int         j;
    sleep(3);
    if (argc > 1)
        acquireSem(sid);
    for (j = 0; j < ts[i].nTimes; j++) {
        printf("%c", ts[i].ch);
        fflush(stdout);
        sleep(ts[i].interval);
        }
    if (argc > 1)
        releaseSem(sid);
    return ts[i].retVal;
    }
}
