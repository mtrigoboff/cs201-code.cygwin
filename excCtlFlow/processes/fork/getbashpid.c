#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("bash process id: %d\n", getppid());
    return 0;
}
