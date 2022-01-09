#include <stdio.h>

// consume rest of line in the input stream
void eatLine ()
{
    while (getchar() != '\n') ;
}

int main (int argc, char **argv)
{
    int     nParsed;
    int     i;
	short	s;
    float   f;
    char    str[8 + 1];             // room for string of length <= 8
                                    // (includes string termination character)
    printf("scanf demo\n\n");
    
    // don't forget to put the & in front of the name of the variable.
    // REALLY BAD THINGS happen when you forget to do that!
    
	// 4-byte integer
    printf("type a 4-byte decimal number: ");
    nParsed = scanf("%d", &i);
    if (nParsed != 1)               // check we parsed all the items requested
        printf("error!\n\n");
    else
        printf("you typed %d\n\n", i);
    eatLine();

	// 2-byte integer
    printf("type a 2-byte decimal number: ");
    nParsed = scanf("%hd", &s);
    if (nParsed != 1)               // check we parsed all the items requested
        printf("error!\n\n");
    else
        printf("you typed %hd\n\n", s);
    eatLine();
    
    printf("type a 4-byte hex number: ");
    nParsed = scanf("%x", &i);
    if (nParsed != 1)               // check we parsed all the items requested
        printf("error!\n\n");
    else
        printf("you typed 0x%08X\n\n", i);
    eatLine();
    
    printf("type a 2-byte hex number: ");
    nParsed = scanf("%hx", &s);
    if (nParsed != 1)               // check we parsed all the items requested
        printf("error!\n\n");
    else
        printf("you typed 0x%04hX\n\n", s);
    eatLine();
    
    printf("type a floating point number: ");
    nParsed = scanf("%f", &f);
    if (nParsed != 1)               // check we parsed all the items requested
        printf("error!\n\n");
    else
        printf("you typed %f\n\n", f);
    eatLine();

    printf("type a string: ");
    nParsed = scanf("%8s", str);    // read in string of length <= 8
                                    // (why don't we need an & in front of str?)
    if (nParsed != 1) {             // check we parsed all the items requested
        eatLine();
        printf("error!\n\n");
        }
    else
        printf("you typed \"%s\"\n\n", str);

    return 0;
}
