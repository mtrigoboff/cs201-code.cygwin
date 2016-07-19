// demonstrates gcc's behavior in compiling comparisons

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main (int argc, char **argv)
{
    int             s1 = 0, s2 = 0;
    unsigned int    u1 = 0, u2 = 0;
    int             x = 0;

    // compare two variables
    if (s1 >= s2)
        x = 0;
    if (u1 >= u2)
        x = 0;

    // compare variable with small constant
    if (s1 >= 3)
        x = 0;
    if (u1 >= 3)
        x = 0;

    // compare variable with negative constant
    if (s1 >= -3)
        x = 0;
    if (u1 >= -3)
        x = 0;

    // compare variable with hex constant

    if (s1 >= 0x80000004)
        x = 0;
    if (s1 >= -3)
        x = 0;
    if (s1 >= 0xFFFFFFFD)       // hex for -3
        x = 0;

    // this doesn't compile into any object code, because the
	// maximum possible value for a signed int is 2,147,483,647
    if (s1 >= 2147483652)       // decimal for 0x80000004
        x = 0;

    if (u1 >= 2147483652)       // decimal for 0x80000004
        x = 0;

    // this compiles to check only if ==
    // (perhaps because 0x7FFFFFFF is the maximum signed int,
    //  so that there's no way that s1 could be larger)
    if (s1 >= 0x7FFFFFFF)
        x = 0;

    // these compile correctly
    if (u1 >= 0x7FFFFFFF)
        x = 0;
    if (u1 >= 0x80000004)
        x = 0;
    if (s1 >= 0x5)
        x = 0;
    if (u1 >= 0x5)
        x = 0;

    return 0;
}
