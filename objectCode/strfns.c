// demonstration of the IA-32 Architecture's string-oriented instructions

#include <stdbool.h>

// compute length of C string (i.e. zero-terminated string)
int strlgth(char *strg)
{
	int		lgth;
	
	asm(
		"	cld							\n"	// set to increment esi and edi
		"	mov		%[strgIn], %%edi	\n"
		"	mov		$0, %%al			\n"	// we're looking for a zero
		"	mov		$0xFFFFFFFF, %%ecx	\n"	// hack! keep ecx from decrementing to zero
		"	repne scasb					\n"	// scan for zero
		"	mov		$0xFFFFFFFF, %%eax	\n"	// ecx's initial value
		"	sub		%%ecx, %%eax		\n"	// eax has length of string + 1
		"	sub		$1, %%eax			\n"	// adjust eax value
		"	mov		%%eax, %[lgthOut]	\n"
		: [lgthOut]		"=m"	(lgth)
		: [strgIn]		"m"		(strg)
		: "edi", "al", "ecx", "eax"
	);
	
	return lgth;
}

// copy a string, given length of source string
void strcopy(char *dest, char *src, int srcLgth)
{
	srcLgth++;							// so that terminal zero will be copied
	asm(
		"	cld							\n"	// set to increment esi and edi
		"	mov		%[srcIn], %%esi		\n"	// esi points to source
		"	mov		%[destIn], %%edi	\n"	// edi points to destination
		"	mov		%[srcLgthIn], %%ecx	\n"	// how many chars to move
		"	rep	 movsb					\n"	// movsb repeats using ecx
		:
		: [destIn]		"m"		(dest),
		  [srcIn]		"m"		(src),
		  [srcLgthIn]	"m"		(srcLgth)
		: "esi", "edi", "ecx"
	);
}

bool strequal(char *s1, char *s2)
{
	int		result;

	asm(
	"		cld							\n"	// set to increment esi and edi
	"		mov		%[s1], %%esi		\n"	// esi points to s1
	"		mov		%[s2], %%edi		\n"	// edi points to s2
	" next:	cmpb	$0, (%%esi)			\n"	// end of s1?
	"		je		end1				\n"	
	"		cmpb	$0, (%%edi)			\n"	// end of s2?
	"		je		ne					\n"	// end of s2, but not s1
	"		cmpsb						\n"	// compare chars, increment esi and edi
	"		jne		ne					\n"	// found unequal chars
	"		jmp		next				\n"	
	" end1:	cmpb	$0, (%%edi)			\n"	// end of s2?
	"		je		eq					\n"	// end of s1 and s2
	"		jmp		ne					\n"	
	" eq:	movl	$1, %[result]		\n"
	"		jmp		done				\n"
	" ne:	movl	$0, %[result]		\n"
	" done:	nop							\n"
	: [result]	"=m"	(result)
	: [s1]		"m"		(s1),
	  [s2]		"m"		(s2)
	: "esi", "edi"
	);

	return result == 1;
}

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main(void)
{
	char	str[] = "length=8";
	char	str0[] = "";
	int		lgth;
	char	str2[sizeof(str)];
	bool	result;
	
	lgth = strlgth(str);
	strcopy(str2, str, lgth);
	lgth = strlgth(str0);

	result = strequal("abc", "abd");
	result = strequal("a", "ab");
	result = strequal("ab", "a");
	result = strequal("abc", "abc");
	result = strequal(str, str2);
}
