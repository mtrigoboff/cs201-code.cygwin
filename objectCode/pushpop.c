#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

static int		stackArray[10];
static int*		stackPtr = &stackArray[10];

static void push(int x)
{
	*--stackPtr = x;
}

static int pop()
{
	return *stackPtr++;
}

int main()
{
	int		val;

	push(1);
	push(2);
	push(3);
	val = pop();
	val = pop();
	val = pop();

	return 0;
}
