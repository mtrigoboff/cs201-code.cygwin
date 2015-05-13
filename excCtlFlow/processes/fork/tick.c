// prints its character at a designated time interval

#include <stdio.h>              // for printf()
#include <stdlib.h>             // for atoi()
#include <unistd.h>             // for sleep()

int main (int argc, char **argv)
{
    char    ch = '+';
    int     seconds = 1;
    int     i;

    // command line arguments:
    //   arg[1]:    character to print
    //   arg[2]:    seconds to wait between printing the character
    //   arg[3]:    if present, print out debugging information

    if (argc >= 4) {
        printf("argc %d: ", argc);
        for (i = 0; i < argc; i++)
            printf("\"%s\",", argv[i]);
        printf("\n");
        }
    if (argc > 1 && argv[1][0])
        ch = argv[1][0];
    if (argc > 2) {
        seconds = atoi(argv[2]);
        if (seconds == 0)
            seconds = 1;
        }
    for (;;) {
        printf("%c", ch);
        fflush(stdout);         // override line buffering so we see single char output
        sleep(seconds);
        }
    return 0;
}
