// demo of GCC inline assembler and various data movement instructions

char    charArray[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
int     intArray[]  = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

int main (int argc, char **argv)
{
    int     localVar = 0x12345678;
    
    // miscellaneous data movement instructions
    asm("       mov     $0x89ABCDEF, %eax       ");
    asm("       mov     $0xFF, %bl              ");
    asm("       movsx   %bl, %eax               ");
    asm("       movzx   %bl, %eax               ");
    
    
    // two instructions in one asm statement
    asm("       mov     $0x12, %al;     mov     $0x34, %ah");
    
    // swapping two values
    asm("       mov     $0xBBBBBBBB, %ebx       ");
    asm("       mov     $0xAAAAAAAA, %eax       ");
    asm("       xchg    %ebx, %eax              ");
    
    // extended asm
    asm("       mov     %0, %%eax               "   : : "m" (localVar));
                                                    // store localVar into eax

    asm("       mov     $4, %ecx                "); // load index register
    
    // int array
    asm("       lea     %0, %%ebx               "   : : "m" (intArray[0]));
                                                    // load address of start of array
    asm("       mov     (%ebx), %eax            "); // get first element of array
    asm("       mov     (%ebx, %ecx, 4), %eax   "); // get indexed element of array
    
    // char array
    asm("       mov     $0, %eax                "); // clear eax
    asm("       lea     %0, %%ebx               "   : : "m" (charArray[0]));
                                                    // load address of start of array
    asm("       mov     (%ebx), %al             "); // get first element of array
    asm("       mov     (%ebx, %ecx, 1), %al    "); // get indexed element of array
    
    return 0;
}
