// print times for execution of parent and children

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork()
#include <sys/wait.h>       // for waitpid()
#include <sys/times.h>      // for times()
#include <time.h>           // for clock()

void burntime(long long int n)
{
    long long int   x = 1;
    long long int   i;
    
    // burn up time
    for (i = 0; i < n; i++)
        x *= i;     
}

int main(int argc, char **argv)
{
    int             status;
    pid_t           pid;
    long long int   n = argc > 1 ? atoll(argv[1]) : 3;       
                    // if arg[1] is present, use it as loop counter limit

    // time-related data
    struct tms  tmsStart, tmsStop;
    clock_t     timesRetStart, timesRetStop;
    clock_t     clockStart, clockStop;
    clock_t     clockTotal;
    double      ticksPerSec = (double) sysconf(_SC_CLK_TCK);
                    // cast to double to force numeric conversion when used
    
    // record start times by the 2 available methods
    clockStart = clock();
    timesRetStart = times(&tmsStart);

    // fork into parent and child processes
    pid = fork();

    // fork() failed
    if (pid < 0) {
        printf("fork error %d\n", pid);
        return -1;
        }

    // code that runs in the child process
    else if (pid == 0) {
        burntime(n);
        printf("child:  looped %lld times\n", n);
        return 212;
        }

    // code that runs in the parent process
    else {
        
        burntime(n);
        printf("parent: looped %lld times\n", n);
        
        waitpid(pid, &status, 0);
        printf("parent: reaps child status 0x%08X\n", status);
        if (WIFEXITED(status))
            printf("parent: child exited normally with %d\n",
                   WEXITSTATUS(status));
        
        // record stop times by the 2 available methods
        timesRetStop = times(&tmsStop);
        clockStop = clock();
        
        // compute execution times based on data from times()
        if (timesRetStart != -1 && timesRetStop != -1 && timesRetStop >= timesRetStart) {
            printf("\ntimer(2) clock ticks per second: %5.1f\n", ticksPerSec);
            printf("\ntimes in ticks\n");
            printf("  parent:   user time %lu, system time %lu\n",
                   tmsStop.tms_utime - tmsStart.tms_utime,
                   tmsStop.tms_stime - tmsStart.tms_stime);
            printf("  children: user time %lu, system time %lu\n",
                   tmsStop.tms_cutime - tmsStart.tms_cutime,
                   tmsStop.tms_cstime - tmsStart.tms_cstime);
            printf("times in seconds\n");
            printf("  parent:   user time %f, system time %f\n",
                   (tmsStop.tms_utime - tmsStart.tms_utime) / ticksPerSec,
                   (tmsStop.tms_stime - tmsStart.tms_stime) / ticksPerSec);
            printf("  children: user time %f, system time %f\n",
                   (tmsStop.tms_cutime - tmsStart.tms_cutime) / ticksPerSec,
                   (tmsStop.tms_cstime - tmsStart.tms_cstime) / ticksPerSec);
            printf("\ntotal time in ticks:   %lu\n", timesRetStop - timesRetStart);
            printf("total time in seconds: %f\n",
                   (timesRetStop - timesRetStart) / ticksPerSec);
            }

        // compute execution time based on data from clock()
        if (clockStop > clockStart)            // time didn't wrap around
            clockTotal = clockStop - clockStart;
            printf("\nclock(3) time: %lu ticks, %f seconds, CLOCKS_PER_SEC %lu\n",
                   clockTotal, ((double) clockTotal) / CLOCKS_PER_SEC, (clock_t) CLOCKS_PER_SEC);
        
        return 0;
        }
}
