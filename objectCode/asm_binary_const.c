// GAS allows the  use of binary constants in assembly language

int main()
{
	asm(
		"		mov		$0b10101010, %al		\n"
	);

	return 0;
}
