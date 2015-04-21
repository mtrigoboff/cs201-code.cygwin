// demonstrates gcc's behavior in compiling comparisons

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main ()
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

    // these both compile as unsigned compare,
    // even though s1 is a signed variable
    if (s1 >= 0x80000004)
        x = 0;
    if (s1 >= -3)
        x = 0;
    if (s1 >= 0xFFFFFFFD)       // hex for -3
        x = 0;

    // this generates a warning, compiles as unsigned compare
    if (s1 >= 2147483652)       // decimal for 0x80000004
        x = 0;

	// this does not generate a warning
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
