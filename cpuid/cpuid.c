// test for presence of CPUID instruction by attempting to change bit 21 of
// EFLAGS as described on page 7 of
// "Intel Processor Identification and the CPUID Instruction", published by
// Intel at http://support.intel.com/support/processors/procid/24161812.htm

#include <stdio.h>

// flags for bits returned in EDX by CPUID 1
#define MMX_FLAG        ((int) 1 << 23)
#define SSE_FLAG        ((int) 1 << 25)
#define SSE2_FLAG       ((int) 1 << 26)
#define PENTIUM4_FLAG   ((int) 1 << 11)

int cpuidAvailable ()
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
void cpuid (int eaxArg, int *eaxAddr, int *ebxAddr, int *ecxAddr, int *edxAddr)
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

int main ()
{
    char            vendorStr[13];
    unsigned int    max;
    unsigned int    extMax;
    int             versionInfo;
    int             features;

    if (! cpuidAvailable()) {
        printf("CPUID instruction is not available on this processor\n");
        return 0;
        }

    cpuid(0, (int *) &max, (int *) vendorStr, (int *) &vendorStr[8], (int *) &vendorStr[4]);
    vendorStr[12] = '\0';
    printf("%-50s %d\n", "maximum value for EAX in normal CPUID call:", max);
    printf("%-50s \"%s\"\n\n", "vendor string:", vendorStr);

    if (max >= 1) {
        // report presence of features
        cpuid(1, &versionInfo, 0, 0, &features);

        // check for features
        printf("%-50s %s\n", "MMX feature:",  (features & MMX_FLAG) ?   "present" : "absent");
        printf("%-50s %s\n", "SSE feature:",  (features & SSE_FLAG) ?   "present" : "absent");
        printf("%-50s %s\n", "SSE2 feature:", (features & SSE2_FLAG) ?  "present" : "absent");

		cpuid(0x80000000, (int *) &extMax, 0, 0, 0);
		printf("\n%-50s 0x%08X\n\n", "maximum value for EAX in extended CPUID call: ", extMax);

		// get brand string, if available
		if (extMax >= 0x80000004) {
			unsigned int    arg;
			int             i;
			int             brandStr[12];

			for (arg = 0x80000002, i = 0; arg <= 0x80000004; arg++, i += 4)
				cpuid(arg, &brandStr[i], &brandStr[i + 1], &brandStr[i + 2], &brandStr[i + 3]);
			printf("brand string:\n\"%s\"\n", (char *) brandStr);
			}
        }

    return 0;
}
