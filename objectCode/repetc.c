// demonstration of the IA-32 Architecture's string-oriented instructions

// fill array with fill character
void fill(char *array, int nChars, char fillChar)
{
	_asm {
			// fill array with fill character
			mov		edi, array
			mov		al, fillChar
			mov		ecx, nChars
			cld							// set direction flag to increment
			rep stosb
	}
}

// add an array of ints
int addIntArray(int *numbers, int lgth)
{
	int		sum;
	
	_asm {
			// add up members of array
			mov		esi, numbers
			mov		ebx, 0				// initialize sum
			mov		ecx, lgth			// loop counter
			cld							// set direction flag to increment
	next:	lodsd
			add		ebx, eax
			loop	next
			mov		sum, ebx
	}
	
	return sum;
}

// compute length of C string (i.e. zero-terminated string)
int strlgth(char *strg)
{
	int		lgth;
	
	_asm {
			cld							// set to increment esi and edi
			mov		edi, strg
			mov		al, 0				// we're looking for a zero
			mov		ecx, 0xFFFFFFFF		// hack! keep ecx from decrementing to zero
			repne scasb					// scan for zero
			mov		eax, 0xFFFFFFFF		// ecx's initial value
			sub		eax, ecx			// eax has length of string + 1
			sub		eax, 1				// adjust eax value
			mov		lgth, eax
	}
	
	return lgth;
}

// copy a string, given length of source string
void strcopy(char *dest, char *src, int srcLgth)
{
	srcLgth++;							// so that terminal zero will be copied
	_asm {
			cld							// set to increment esi and edi
			mov		esi, src			// esi points to source
			mov		edi, dest			// edi points to destination
			mov		ecx, srcLgth		// how many chars to move
			rep		movsb				// movsb repeats using ecx
	}
}

// check whether two strings are equal
//   This is a three-pass algorithm and makes two function calls,
//   so it's slower but the logic is clearer.
int strequal3(char *s1, char *s2)
{
	int		s1Lgth;
	int		s2Lgth;
	int		distToEnd;
	
	if (s1 == s2)						// comparing a string to itself
		return 1;
	
	// get string lengths, make sure they're equal
	s1Lgth = strlgth(s1);
	s2Lgth = strlgth(s2);
	if (s1Lgth != s2Lgth)
		return 0;
	
	// the two strings are of equal length, so compare them char by char
	_asm {
			mov		ecx, s1Lgth			// only need to compare within the 2 strings
			add		ecx, 1				// so that ecx won't go to zero while ...
										// ... we're still comparing characters
			cld							// set to increment esi and edi
			mov		esi, s1				// esi points to s1
			mov		edi, s2				// edi points to s2
			repe cmpsb					// find first place where chars are not equal
			mov		distToEnd, ecx		// how far from end of str when we stopped
	}

	return distToEnd == 0;				// strings equal only if we got to the end
}

// check whether two strings are equal
//   This one is a one-pass algorithm and makes no function calls,
//   so it should be much faster, but pays the price with more complex logic.
int strequal1(char *s1, char *s2)
{
	_asm {
			cld							// set to increment esi and edi
			mov		esi, s1				// esi points to s1
			mov		edi, s2				// edi points to s2
	next:	cmp		[esi], 0			// end of s1?
			je		endS1
			cmp		[edi], 0			// end of s2?
			je		notEqual			// end of s2, but not s1
			cmpsb						// compare chars, increment esi and edi
			jne		notEqual			// found unequal chars
			jmp		next
	endS1:	cmp		[edi], 0			// end of s2?
			je		equal				// end of s1 and s2
			jmp		notEqual
	}

notEqual:	return 0;
equal:		return 1;
}

int main(void)
{
	char	fillArray[] = {"--------"};
	int		numbers[] = {1, 2, 3, 4, 5};
	int		sum;
	char	str[] = "length=8";
	char	str0[] = "";
	int		lgth;
	char	str2[sizeof(str)];
	
	fill(fillArray, sizeof(fillArray) - 1, '+');
	sum = addIntArray(numbers, sizeof(numbers) / sizeof(int));
	lgth = strlgth(str);
	strcopy(str2, str, lgth);
	lgth = strlgth(str0);

	strequal3("abc", "abd");
	strequal3("a", "ab");
	strequal3("ab", "a");
	strequal3("abc", "abc");
	strequal3(str, str2);

	strequal1("abc", "abd");
	strequal1("a", "ab");
	strequal1("ab", "a");
	strequal1("abc", "abc");
	strequal1(str, str2);
}
