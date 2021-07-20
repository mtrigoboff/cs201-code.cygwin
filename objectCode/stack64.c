#pragma GCC diagnostic ignored "-Wunused-variable"

long fn(long a, long b, long c, long d, long e, long f, long g)
{
	return 0x2222222222222222;
}

int main()
{
	int r =	fn(0xAAAAAAAAAAAAAAAA,
			   0xBBBBBBBBBBBBBBBB,
			   0xCCCCCCCCCCCCCCCC,
			   0xDDDDDDDDDDDDDDDD,
			   0xEEEEEEEEEEEEEEEE,
			   0xFFFFFFFFFFFFFFFF,
			   0x1111111111111111);
	
	return 0;
}
