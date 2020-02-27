#pragma GCC diagnostic ignored "-Wunused-variable"

int main(void)
{
	// problem incrementing float == 2^24
	float f =			16777216;
	float fPlusOne =	f + 1.0;
	float fPlusTwo = 	16777218;

	// no problem with double for this value
	double d =			16777216;
	double dPlusOne =	d + 1.0;
	double dNext =		16777217;
	
	return 0;
}
