#include <stdio.h>

// test for presence of CPUID instruction by attempting to change bit 21 of EFLAGS
// as described on page 7 of "Intel Processor Identification and the CPUID Instruction",
// published by Intel
//
int cpuidAvailable()
{
    int     eflags1, eflags2;
    int     bitMask21 = 1 << 21;                    // mask for bit 21

    asm("       pushf                       \n"     // push EFLAGS value onto stack
        "       pop     %%eax               \n"     // pop EFLAGS value into EAX
        "       mov     %%eax, %[eflags1]   \n"
        "       xor     %[bm21], %%eax      \n"     // change bit 21 of EFLAGS value
        "       push    %%eax               \n"     // push changed value onto stack
        "       popf                        \n"     // store changed value in EFLAGS
        "       pushf                       \n"     // push EFLAGS value onto stack
        "       pop     %[eflags2]          \n"
        :   [eflags1]   "=m"    (eflags1),          // outputs
            [eflags2]   "=m"    (eflags2)
        :   [bm21]      "m"     (bitMask21)         // inputs
        :   "eax"                                   // clobbers
    );

    return eflags1 != eflags2;                      // check whether value changed
}

// cpuid arguments:
//      eaxArg:     will be stored into EAX before CPUID is called
//      eaxAddr:    address for storing data returned by CPUID in EAX, or zero
//      ebxAddr:    address for storing data returned by CPUID in EBX, or zero
//      ecxAddr:    address for storing data returned by CPUID in ECX, or zero
//      edxAddr:    address for storing data returned by CPUID in EDX, or zero
//
void cpuid(unsigned int eaxArg, unsigned int *eaxAddr, unsigned int *ebxAddr,
                                unsigned int *ecxAddr, unsigned int *edxAddr)
{
    int     eax, ebx, ecx, edx;

    asm("       mov     %[eaxArg], %%eax    \n"
        "       cpuid                       \n"
        "       mov     %%eax, %[eax]       \n"
        "       mov     %%ebx, %[ebx]       \n"
        "       mov     %%ecx, %[ecx]       \n"
        "       mov     %%edx, %[edx]       \n"
        :   [eax]       "=m"    (eax),      // outputs
            [ebx]       "=m"    (ebx),
            [ecx]       "=m"    (ecx),
            [edx]       "=m"    (edx)
        :   [eaxArg]    "m"     (eaxArg)    // inputs
        :   "eax", "ebx", "ecx", "edx"      // clobbers
    );

    // only store values if non-zero address was provided
    if (eaxAddr)
        *eaxAddr = eax;
    if (ebxAddr)
        *ebxAddr = ebx;
    if (ecxAddr)
        *ecxAddr = ecx;
    if (edxAddr)
        *edxAddr = edx;
}

int main()
{
    unsigned int	max;
    unsigned int	extMax;
    int             hdrWidth = 32;
	char			vendorStr[13];
	char			brandStr[49];

    printf("\n");
    if (! cpuidAvailable()) {
        printf("CPUID instruction is not available on this processor\n\n");
        return 0;
        }

    cpuid(0, &max, (unsigned int *) vendorStr,
                   (unsigned int *) &vendorStr[8],
                   (unsigned int *) &vendorStr[4]);
    vendorStr[12] = '\0';
    printf("%-*s %d\n", hdrWidth, "max EAX value, normal range:", max);
    printf("%-*s \"%s\"\n\n", hdrWidth, "vendor string:", vendorStr);

    cpuid(0x80000000, &extMax, 0, 0, 0);
    printf("%-*s %d(0x%08X)\n", hdrWidth,
           "max EAX value, extended range:", extMax & 0x7FFFFFFF,
           extMax);
    if (extMax >= 0x80000004) {
        unsigned int    arg;
        int             i;

        for (arg = 0x80000002, i = 0; arg <= 0x80000004; arg++, i += 16)
            cpuid(arg, (unsigned int *) &brandStr[i],
                       (unsigned int *) &brandStr[i + 4],
                       (unsigned int *) &brandStr[i + 8],
                       (unsigned int *) &brandStr[i + 12]);
        brandStr[48] = '\0';
        printf("%-*s \"%s\"\n", hdrWidth, "brand string:", brandStr);
        }

    printf("\n");
    return 0;
}
