#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char **argv)
{
    char    ruler[] = "0123456789";
    char    iHeader[] = "the value of i is:  ";
    char    piHeader[] = "the value of pi is: ";
    char	ch = '$';
    float   pi = M_PI;
    double  dpi = M_PI;

	// 4-byte integers
    int     i = 5;
    int     w = 12, r = 8;
    
	// 2-byte integers
	signed short	ss;		// 'signed' is assumed if not specified
	unsigned short	us;

    printf("Demo of the printf function\n\n");

    // printing a character

	printf("char variable:     %c\n\n", ch);

    // printing strings
    
    printf("default:           \"%s\"\n", ruler);
    printf("field of width 20: \"%20s\"\n", ruler);
    printf("left justified:    \"%-20s\"\n", ruler);
    printf("field of width 5:  \"%5s\"\n", ruler);

    printf("\nruler:\n");
    for (i = 0; i < 5; i++)
        printf("%s", ruler);	// print string, no return
    printf("\n\n");				// skip lines
    
    // printing 4-byte integers
    
    i = 2345;
    printf("%s%d\n", iHeader, i);	// default integer format
        // note the use of TWO format specifiers, %s and %d
    
    // print number in field of width 8, right justified
    printf("%s%8i\n", iHeader, i);
    
    // print number in field of width 8, right justified, with leading zeros
    printf("%s%08i\n", iHeader, i);
    
    // print number in field of width 8, left justified
    printf("%s%-8i\n\n", iHeader, i);

    // printing 2-byte integers (note use of 'h' in format specifier)
	
	ss = 1000;
	printf("signed short:   %6hd, 0x%04hX\n", ss, ss);
	ss = -1;
	printf("signed short:   %6hd, 0x%04hX\n", ss, ss);
    
	us = 1000;
	printf("unsigned short: %6hu, 0x%04hX\n", us, us);
	us = 65535;
	printf("unsigned short: %6hu, 0x%04hX\n\n", us, us);
    
    // printing an address
	
    printf("address of ruler variable: 0x%08lX\n", (long) ruler);
    printf("address of ruler variable: %8p\n\n", ruler);

    // printing floating point numbers
    
    printf("%s%f\n", piHeader, pi);		// default format

    // print number in field of width 8,
    // with 3 places to the right of the decimal point
    printf("%s%8.3f\n", piHeader, pi);
    
    // print number with 3 places to the right of the decimal point
    printf("%s%.3f\n", piHeader, pi);
    
    // print number in field of width 12
    printf("%s%12f\n\n", piHeader, pi);
    
	// print double precision floating point number
    printf("%s%f\n", "printing a double float:    ", dpi);	// default format
    
    // print number in scientific notation
    printf("the value of 10000 * pi is: %e\n\n", 10000 * pi);
    
    // use of asterisk in print format specifier:
    //     print number in field of width specified by w,
    //     with places to the right of the decimal point specified by r
    // Using the asterisk allows the field width and number of places
    // to the right of the decimal point to be specified at run time,
    // instead of by a fixed value at compile time.
    printf("%s%*.*f\n\n", piHeader, w, r, pi);
    
    return 0;
}
