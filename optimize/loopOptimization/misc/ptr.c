#define ARRAY_SIZE      1000

int main(int argc, char **argv)
{
    double  array[ARRAY_SIZE];
    double  *p;

    for (p = array; p < &array[ARRAY_SIZE]; p++) {
        // walks pointer p through array, a fast way of traversing an array
        }
    return 0;
}
