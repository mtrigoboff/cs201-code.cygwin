// demonstrates use of goto to handle errors in 5 stage process,
// using malloc() and free() to simulate the stages

#include <stdlib.h>

// returns 0 if no error, else error number in [1..5]
int main(int argc, char** argv)
{
	int		crash;		// where to "crash" via cmd line arg
	int		err;		// error code
	char*	mem1;
	char*	mem2;
	char*	mem3;
	char*	mem4;
	char*	mem5;

	crash = argc > 1 ? atoi(argv[1]) : 0;
		// no cmd line arg means no "crash"

	mem1 = malloc(1024);		// stage 1
	if (crash == 1) {
		err = 1;
		goto err1;
		}
	mem2 = malloc(1024);		// stage 2
	if (crash == 2) {
		err = 2;
		goto err2;
		}
	mem3 = malloc(1024);		// stage 3
	if (crash == 3) {
		err = 3;
		goto err3;
		}
	mem4 = malloc(1024);		// stage 4
	if (crash == 4) {
		err = 4;
		goto err4;
		}
	mem5 = malloc(1024);		// stage 5
	if (crash == 5) {
		err = 5;
		goto err5;
		}

	err = 0;

// cleanup code

err5:
	free(mem5);		// unwind stage 5
err4:
	free(mem4);		// unwind stage 4
err3:
	free(mem3);		// unwind stage 3
err2:
	free(mem2);		// unwind stage 2
err1:
	free(mem1);		// unwind stage 1

	return err;
}
