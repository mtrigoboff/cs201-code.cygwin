// time combine/vector functions

// call from command line: combines [nTimes [vLgth [version]]]

#include <stdio.h>
#include <stdlib.h>
#include "combine.h"

int main (int argc, char** argv)
{
    // variables for command line arguments
    int         nTimes = 2000;
    int         version = 1;
    int         vLgth = 2000;
    
    // array of function pointers for the various versions of the algorithm
    CombineFn   cfns[] = {combine1, combine2, combine3, combine4, combine5};

    int         i;
    data_t      dest;
    vec_ptr     vp;

    if (argc >= 2)
        nTimes = atoi(argv[1]);
    if (argc >= 3)
        vLgth = atoi(argv[2]);
    if (argc >= 4) {
        version = atoi(argv[3]);
        if (version < 1 || version > 5)
            version = 1;
        }
    
    printf("running with nTimes = %d, vLgth = %d, version = %d\n", nTimes, vLgth, version);
    
    // allocate the vector
    vp = new_vec(vLgth);
    if (! vp) {
        printf("can't allocate vector\n");
        return -1;
        }
    
    // run the chosen version of the algorithm on the vector
    for (i = 0; i < nTimes; i++)
        (*cfns[version - 1])(vp, &dest);

    return 0;
}
