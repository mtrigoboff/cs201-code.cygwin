// demonstrates the use of a string operation (stosb)
// to store '+' into each element of an array of chars

int main (void)
{
    int     LGTH = 5;
    char    array[] = {'a', 'b', 'c', 'd', 'e'};
    
    // fill array with new character
    asm("       lea     %[array], %%edi         \n"
        "       mov     $'+', %%al              \n"
        "       mov     %[LGTH], %%ecx          \n"
        "       rep stosb                       \n"

        :   [array]     "=m"    (array)         // outputs
        :   [LGTH]      "m"     (LGTH)          // inputs
        :   "ecx", "edi"                        // clobbers
    );

    return 0;
}
