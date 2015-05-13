// code that looks like it only allows one process at a time
// into the "critical section", but this code would actually
// be ineffective at enforcing that limit

#include <unistd.h>

// assume that all processes will see ONE instance of this
// global variable, even though that's not actually true in Unix
int     count = 0;
    
int main ()
{
    while (count > 0)
        sleep(1);
    
    count++;                // process marks its presence
    
    // critical section
    
    count--;                // process frees the critical section
    
    return 0;
}
