// achieves inter-process communication using a pipe and fcntl()
//
// Thanks to Winter 2020 student Charlie Hall for pointing out
// that fcntl() could be used for this.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork(), sleep(), pipe()
#include <fcntl.h>			// for fcntl()
#include <errno.h>			// for EAGAIN
#include <sys/wait.h>       // for waitpid()

static int              comm[2];
static char             cmd = 'x';

int main()
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

		// set input side of pipe to non-blocking
		{
		int		fdFlags;
		
		fdFlags = fcntl(comm[0], F_GETFL);
		fdFlags |= O_NONBLOCK;
		fcntl(comm[0], F_SETFL, fdFlags);
		}

        // child waits until parent tells it to start
		for (;;) {
			int		readRet;
			
			readRet = read(comm[0], &cmd, 1);
			if (readRet == -1 && errno == EAGAIN)
				sleep(1);
			else
				break;
			}

        // child runs until parent tells it to stop
        for (;;) {
			int		readRet;
			
			readRet = read(comm[0], &cmd, 1);
			if (readRet == -1 && errno == EAGAIN) {
				printf("%c", '.');
				fflush(stdout);     // override line buffering so we see single char output
				sleep(1);
				}
			else
				break;
        	}

        close(comm[0]);
        printf("child exits\n");
        return 1;
        }

    // code that runs in the parent process
    else {
        close(comm[0]);         // parent doesn't need input side of pipe
        printf("parent waiting\n");
        write(comm[1], &cmd, 1);        // tell child to start
        getchar();
        write(comm[1], &cmd, 1);        // tell child to stop
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
