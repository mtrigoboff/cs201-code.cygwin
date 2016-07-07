int main()
{
	signed int		s = 0xFFFFFFFF;
	unsigned int	u = 0xFFFFFFFF;

	if (s > 3)
		s = 0;
	if (u > 3)
		u = 0;

	return 0;
}
