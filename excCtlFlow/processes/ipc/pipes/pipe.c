// implements a tiny communications "protocol" using a pipe

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for fork(), sleep(), pipe()
#include <sys/wait.h>       // for waitpid()

// error response definitions
#define READ_ERR        -2
#define WRITE_ERR       -3
#define PROTOCOL_ERR    -1

// protocol command definitions
#define OPEN_CMD        -12
#define CLOSE_CMD       -13
#define ACK_CMD         -10     // acknowledge receiving command

static int      toChild[2];     // pipe to child
static int      fromChild[2];   // pipe from child

static int      in, out;        // file descriptors for processes to use

char readPipe ()
{
    char    ch;
    
    if (read(in, &ch, 1) == 1)
        return ch;
    else {
        printf("readPipe: read error\n");
        exit(READ_ERR);
        }
}

void writePipe (char ch)
{
    if (write(out, &ch, 1) != 1) {
        printf("writePipe: write error\n");     
        exit(WRITE_ERR);
        }
}

void getCmd (char cmd)
{
    char    ch = readPipe();
    
    if (ch == cmd)
        writePipe(ACK_CMD);
    else {
        printf("getCmd: protocol error\n");
        exit(PROTOCOL_ERR);
        }
}

void sendCmd (char cmd)
{
    char    ch;
    
    writePipe(cmd);
    if ((ch = readPipe()) != ACK_CMD) {
        printf("sendCmd: protocol error, read '%d' 0x%X\n", ch, ch & 0xFF);
        exit(PROTOCOL_ERR);
        }
}

char getData ()
{
    char    ch = readPipe();

    writePipe(ACK_CMD);
    return ch;
}

void sendData (char ch)
{
    char    c;

    writePipe(ch);
    if ((c = readPipe()) != ACK_CMD) {
        printf("sendCmd: protocol error, read '%d' 0x%X\n", ch, ch & 0xFF);
        exit(PROTOCOL_ERR);
        }
    printf("parent: '%c' acknowledged\n", ch);
}

int main (int argc, char **argv)
{
    int     status;
    pid_t   pid;
    char    ch;
    int     nChars;
    int     i;

    // set up pipe to child
    if (pipe(toChild)) {
        printf("pipe to child: error\n");
        return -1;
        }

    // set up pipe from child
    if (pipe(fromChild)) {
        printf("pipe from child: error\n");
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
    
        // set up pipes for child
        close(fromChild[0]);
        out = fromChild[1];
        in = toChild[0];
        close(toChild[1]);

        // do childish things
        printf("child:  waiting for OPEN\n");
        getCmd(OPEN_CMD);
        printf("child:  received OPEN\n");
        nChars = getData();
        printf("child:  received nChars = %d\n", nChars);
        for (i = 0; i < nChars; i++) {
            ch = getData();
            printf("child:  received '%c'\n", ch);
            sleep(1);   // 1 second
            }
        getCmd(CLOSE_CMD);
        close(in);
        close(out);
        printf("child:  exits\n");
        return 210;
        }

    // code that runs in the parent process
    else {
    
        // if arg[1] is present, use it to initialize initial character to send
        ch =        argc > 1 ? argv[1][0] : 'a';       

        // if arg[2] is present, use it to initialize number of characters to send
        nChars =    argc > 2 ? atoi(argv[2]) : 3;       

        // set up pipes for parent
        close(toChild[0]);
        out = toChild[1];
        in = fromChild[0];
        close(fromChild[1]);

        // do parental things
        printf("parent: sends OPEN\n");
        sendCmd(OPEN_CMD);
        printf("parent: sends nChars = %d\n", nChars);
        sendData(nChars);
        for (i = 0; i < nChars; i++) {
            printf("parent: sends '%c'\n", ch);
            sendData(ch++);
            }
        printf("parent: sends CLOSE\n");
        sendCmd(CLOSE_CMD);
        waitpid(pid, &status, 0);
        printf("parent: reaps child status 0x%08X\n", status);
        if (WIFEXITED(status))
            printf("parent: child exited normally with %d\n", WEXITSTATUS(status));
        close(in);
        close(out);
        printf("parent: exits\n");
        return 0;
        }
}
