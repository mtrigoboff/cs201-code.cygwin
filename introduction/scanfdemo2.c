#include <stdio.h>
#include <stdbool.h>

// consume rest of line in the input stream
void eatLine()
{
    while (getchar() != '\n') ;
}

bool getNumber(char* str, char* formatStr, void* n)
{
	char	trailing;

	return sscanf(str, formatStr, n, &trailing) == 1;
}

#define MAX_STR_LGTH		20
static char* strFormatSpec = "%20s";

int main(int argc, char **argv)
{
	int		nParsed;
    int     n;
    float   f;
    char    str[MAX_STR_LGTH + 1];
	          // room for string of length <= MAX_STR_LGTH
              // (includes string termination character)

    printf("scanf demo 2\n\n");
    
    // don't forget to put the & in front of the name of the variable.
    // REALLY BAD THINGS happen when you forget to do that!
    
    printf("type a decimal number: ");
	scanf(strFormatSpec, str); 
    if (! getNumber(str, "%d %c", &n)) {
        eatLine();
        printf("error!\n\n");
        }
    else
        printf("you typed %d\n\n", n);

    printf("type a floating point number: ");
	scanf(strFormatSpec, str); 
    if (! getNumber(str, "%f %c", &f)) {
        eatLine();
        printf("error!\n\n");
        }
    else
        printf("you typed %f\n\n", f);
    
    printf("type a hex number: ");
	scanf(strFormatSpec, str); 
    if (! getNumber(str, "%x %c", &n)) {
        eatLine();
        printf("error!\n\n");
        }
    else
        printf("you typed 0x%08X\n\n", n);
    
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
