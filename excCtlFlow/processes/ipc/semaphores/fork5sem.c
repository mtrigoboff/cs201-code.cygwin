// demonstrates multiple children which will cooperate using
// a semaphore if a command-line argument is given
//
// arguments
//		1: the number of processes that can simultaneously "grab" the
//		   semaphore. 2 is a good argument to try with this code.
//		2: the number of "tick processes" to create
//
// If called with no arguments, child processes won't use semaphore.

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>			// for fork()
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>		// for semaphore
#include <sys/wait.h>		// for waitpid()

// #define PRINT

typedef struct {
	char	ch;				// character to print
	int		nTimes;			// how many times to print ch
	int		retVal;			// value to return
	pid_t	pid;
	}
TickSpecifier;

TickSpecifier *ts;			// pointer to array of tick proccess specifiers

// character for each process to print
char tickChars[] = {'+', '-', '!', '$', '@', '.', ':', '^', '\\', '/'};

void semcall(int sid, int op)    /* call Unix/Linux system call semop */
{
	// add op to the value of the semaphore
	// (op may be negative, which will reduce the value)
	struct sembuf sb;		// 1-element "array"
	sb.sem_num = 0;			// operate on the first (and only) semaphore
	sb.sem_op = op;			// number to add(subtract) to(from) semaphore value
	sb.sem_flg = SEM_UNDO;	// will be undone if this process terminates
	if (semop(sid, &sb, 1) == -1) {		// perform requested operation
		printf("Error in semop\n");
		exit(-1);
		}
}

void initSem(int sid, int nAllowed)
{
	// initialize value of semaphore to nAllowed, which will allow
	// that many processes to acquire this semaphore at the same time
	semcall(sid, nAllowed);
}

void acquireSem(int sid)
{
	// value of semaphore must be > 0,
	// otherwise this will wait until it is restored to > 0
	// and then subtract 1 from it and acquire the semaphore
	// for the calling process
	semcall(sid, -1);
}

void releaseSem(int sid)
{
	// add 1 to the value of the semaphore,
	// allowing some other process to acquire it
	semcall(sid, 1);
}

int main(int argc, char **argv)
{
	int		status;
	pid_t	pid;
	int		i;
	int		nTimes;
	int		sid;
	int		nAllowed =		-1;	// how many process at a time allowed in semaphore
	int		nTickProcesses = 3;	// how many tick processes to create
	bool	first;

	// check validity of command line args 
	if (argc > 1) {
		nAllowed = atoi(argv[1]);
		if (nAllowed < 1) {
			printf("bad arg: %s\nneed a non-negative number to initialize semaphore\n",
				   argv[1]);
			return 1;
			}
		}
	if (argc > 2) {
		nTickProcesses = atoi(argv[2]);
		if (nTickProcesses < 1) {
			printf("bad arg: %s\nneed a non-negative number of tick processes\n",
				   argv[2]);
			return 2;
			}
		else if (nTickProcesses > sizeof(tickChars)) {
			printf("bad arg: %s\nnumber of tick processes must be <= %d\n",
				   argv[2], sizeof(tickChars));
			return 3;
			}
		}

	// report whether or not children will be using the semaphore
	printf("children will %sbe using semaphore", nAllowed > 0 ? "" : "not ");
	if (nAllowed > 0)
		printf(" with initial value %d", nAllowed);
	printf("\n");

	// create the semaphore
	//
	// IPC_PRIVATE means create a new semaphore each time this runs.
	// Semaphores are "persistent", and this flag must be used to create
	// a unique new one.  "man semget" states that IPC_PRIVATE was an
	// unfortunate choice of name, and that IPC_NEW would have been better.
	if ((sid = semget(IPC_PRIVATE, 1, 0600 | IPC_CREAT)) == -1) {
		printf ("couldn't get semaphore\n");
		exit(-1);
		}

	// create the tick process specifier array
	//   start with tick character '!' - add one to get ascii character for next process
	ts = malloc(nTickProcesses * sizeof(TickSpecifier));
	printf("%d processes: ", nTickProcesses);
	first = true;
	for (i = 0, nTimes = 4; i < nTickProcesses; i++, nTimes += 2) {
		ts[i].ch = tickChars[i];
		ts[i].nTimes = nTimes;
		ts[i].retVal = i + 1;
		printf("%s'%c' %d times", first ? "" : ", ", ts[i].ch, ts[i].nTimes);
		first = false;
		}
	printf("\n");

	for (i = 0; i < nTickProcesses; i++) {
		pid = fork();
		if (pid == 0)
			goto child;
		else {
			ts[i].pid = pid;	// this might be < 0 if fork() error
			#ifdef PRINT
			printf("forked pid %d with ch '%c', nTimes %d\n",
				pid, ts[i].ch, ts[i].nTimes);
			#endif
			}
		}

	// if semaphore will be used,
	//     children can't start until it is initialized
	if (nAllowed > 0)
		initSem(sid, nAllowed);

	for (i = 0; i < nTickProcesses; i++) {
		pid = ts[i].pid;
		if (pid > 0) {
			#ifdef PRINT
			printf("\nabout to wait for pid %d\n", pid);
			#endif
			waitpid(pid, &status, 0);
			}
		}
	printf("\n");
	free(ts);
	return 0;

child: {
	// code that runs in the child process
	int		j;
	int		ret;

	if (nAllowed > 0)
		acquireSem(sid);
	else
		sleep(1);	// give parent time to print status info
	for (j = 0; j < ts[i].nTimes; j++) {
		printf("%c", ts[i].ch);
		fflush(stdout);
		sleep(1);
		}
	if (nAllowed > 0)
		releaseSem(sid);
	ret = ts[i].retVal;
	free(ts);
	return ret;
	}
}
