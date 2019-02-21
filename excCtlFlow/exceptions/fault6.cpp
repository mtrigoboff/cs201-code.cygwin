// C++ exception mechanism can't handle this

#include <iostream>
#include <signal.h>
#include <stdlib.h>

using namespace std;

void signalHandler(int signal)
{
    cout << "signalHandler received signal " << signal << endl;
	throw signal;
}

int main(int argc, char **argv)
{
    double      numerator = 1.0;
    double      denominator = 1.0;
    double      quotient;
    short       fcw;                            // used to unmask fp exceptions

    if (signal(SIGFPE, signalHandler) == SIG_ERR) {
        cout << "signal error" << endl;
		return -1;
		}

    // set fp control word to unmask zero divide exception
    asm("   fstcw   %[fcwOut]           \n"     // get fp control word
        "   andw    $0xFFFB, %[fcwIn]   \n"     // unmask zero divide exception
        "   fldcw   %[fcwIn]            \n"     // store fp control word
        : [fcwOut]     "=m"     (fcw)           // outputs
        : [fcwIn]      "m"      (fcw));         // inputs

    // get denominator from user, if arg is present
    if (argc > 1)
        denominator = atof(argv[1]);

    cout << "about to divide " << numerator << " by " << denominator << endl;
	try {
		quotient = numerator / denominator;    		// perform the division
		cout << "quotient = " << quotient << endl;  // print result, if we get here
		}
	catch (...) {
        cout << "zero divide error" << endl;
		}

    return 0;
}
