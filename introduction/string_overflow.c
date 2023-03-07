#include <stdio.h>

// consume rest of line in the input stream
void eatLine ()
{
    while (getchar() != '\n') ;
}

int main (int argc, char **argv)
{
    int     nParsed;
    char    str[8 + 1];             // room for string of length <= 8
                                    // (includes string termination character)
    printf("string overflow demo\n\n");
    
    // don't forget to put the & in front of the name of the variable.
    // REALLY BAD THINGS happen when you forget to do that!
    
	for (int i = 0; i < 5; i++) {
		printf("type a string: ");
		nParsed = scanf("%8s", str);    // read in string of length <= 8
										// (why don't we need an & in front of str?)
		if (nParsed != 1) {             // check we parsed all the items requested
			eatLine();
			printf("error!\n\n");
			}
		else
			printf("you typed \"%s\"\n\n", str);
		}

    return 0;
}
